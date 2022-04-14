// Copyright 2022 Kurnikova Anastasia
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include "../../modules/task_3/kurnikova_a_sparse_ccs_mult/sparse_ccs_mult.h"
#include "tbb/tbb.h"

mymat::mymat(int v, int h, int nz) {
    countv = v;
    counth = h;
    cols.resize(h + 1);
    countnz = nz;
    num.resize(nz);
    rows.resize(nz);
}

mymat t(const mymat* a) {
    mymat at(a->counth, a->countv, a->countnz);
    for (int i = 0; i < a->countnz; i++)
        at.cols[a->rows[i] + 1]++;
    int tmp;
    int sum = 0;
    for (int i = 1; i < a->countv + 1; i++) {
        tmp = at.cols[i];
        at.cols[i] = sum;
        sum += tmp;
    }
    int start, end, it, b, c;
    double v;
    for (int i = 0; i < a->counth; i++) {
        start = a->cols[i];
        end = a->cols[i + 1];
        it = i;
        for (int j = start; j < end; j++) {
            v = a->num[j];
            b = a->rows[j];
            c = at.cols[b + 1];
            at.num[c] = v;
            at.rows[c] = it;
            at.cols[b + 1]++;
        }
    }
    return at;
}

double vecmult(const mymat* a, const mymat* at, int n, int m) {
    double ch = 0;
    for (int i = at->cols[n]; i < at->cols[n + 1]; i++)
        for (int j = a->cols[m]; j < a->cols[m + 1]; j++)
            if (at->rows[i] == at->rows[j]) {
                ch += at->num[i] * a->num[j];
                break;
            }
    return ch;
}

struct help {
    mymat at, b;
    std::vector<int>* rows;
    std::vector<int>* reacols;
    std::vector<double>* num;
    help(const mymat* atat, const mymat* bb,
        std::vector<int>* rowsrows,
        std::vector<int>* reacolsreacols,
        std::vector<double>* numnum) :
        at(*atat), b(*bb), rows(rowsrows),
        reacols(reacolsreacols), num(numnum) { }

    void operator()(const tbb::blocked_range<int>& n) const {
        int emp, c1 = b.counth;
        double tmp;
        for (int i = n.begin(); i < n.end(); i++) {
            if (i < c1)
                c1 = i;
            emp = 0;
            for (int j = 0; j < at.counth; j++) {
                tmp = vecmult(&at, &b, j, i);
                if (tmp != 0) {
                    num[i].push_back(tmp);
                    rows[i].push_back(j);
                    emp++;
                }
            }
            (*reacols)[i] = emp;
        }
    }
};

mymat result(const mymat* a, const mymat* b) {
    mymat ready(a->countv, b->counth, 0);
    mymat at = t(a);
    std::vector<int>* rows = new std::vector<int>[ready.counth];
    std::vector<double>* num = new std::vector<double>[ready.counth];
    tbb::parallel_for(tbb::blocked_range<int>(0, b->counth, 10),
        help(&at, b, rows, &ready.cols, num));
    int pme = 0;
    for (int i = 0; i < ready.counth; i++) {
        int tmp = ready.cols[i];
        ready.cols[i] = pme;
        pme += tmp;
    }
    ready.cols[ready.counth] = pme;
    ready.num.resize(ready.cols.back());
    ready.rows.resize(ready.cols.back());
    int j = 0;
    for (int i = 0; i < ready.counth; i++) {
        if (num[i].size() > 0) {
            memcpy(&ready.num[j], &num[i][0],
                num[i].size() * sizeof(double));
            memcpy(&ready.rows[j], &rows[i][0],
                num[i].size() * sizeof(int));
            j += num[i].size();
        }
    }
    delete[] num;
    delete[] rows;
    return ready;
}

bool operator==(const mymat& a, const mymat& b) {
    return a.num == b.num && a.rows == b.rows &&
        a.cols == b.cols && a.countv == b.countv;
}

mymat randmat(int countv, int counth) {
    int a, b, c;
    std::vector<int> r;
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    a = gen() % static_cast<int>(sqrt(countv * counth));
    b = (a / counth == 0) ? 1 : a / counth;
    mymat d(countv, counth, 0);
    d.countnz = b * counth;
    for (int i = 0; i < counth; i++) {
        for (int j = 0; j < b; j++) {
            d.num.push_back(gen() % static_cast<int>(countv * counth));
            c = gen() % static_cast<int>(countv);
            while (std::find(r.begin(), r.end(), c) != r.end())
                c = gen() % static_cast<int>(countv);
            d.rows.push_back(c);
        }
        d.cols[i] = i * b;
    }
    d.cols[counth] = counth * b;
    return d;
}

mymat seqresult(const mymat* a, const mymat* b) {
    mymat ready(a->countv, b->counth, 0);
    mymat at(t(a));
    double tmp;
    for (int j = 0; j < b->counth; j++) {
        int emp = 0;
        for (int i = 0; i < at.counth; i++) {
            tmp = vecmult(b, &at, i, j);
            if (tmp != 0) {
                ready.num.push_back(tmp);
                ready.rows.push_back(i);
                emp++;
            }
        }
        ready.cols[j + 1] = emp + ready.cols[j];
    }
    return ready;
}
