// Copyright 2022 Kurnikova Anastasia
#include <vector>
#include "../../modules/task_1/kurnikova_a_sparse_ccs_mult/sparse_ccs_mult.h"

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

mymat result(const mymat* a, const mymat* b) {
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

bool operator==(const mymat& a, const mymat& b) {
    return a.num == b.num && a.rows == b.rows &&
        a.cols == b.cols && a.countv == b.countv;
}
