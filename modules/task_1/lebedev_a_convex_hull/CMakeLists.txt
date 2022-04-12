get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

if ( USE_SEQ )
    set(ProjectId "${ProjectId}_seq")
    project( ${ProjectId} )
    message( STATUS "-- " ${ProjectId} )

    include( cmake/OpenCVGet.txt )

    set(OPENCV_VERSION 4.3.0)
    set(DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/tmp")
    set(OPENCV_SRC "${DOWNLOAD_DIR}/opencv-${OPENCV_VERSION}")
    if (NOT EXISTS "${OPENCV_SRC}")
	download_opencv(${DOWNLOAD_DIR} ${OPENCV_VERSION})
        extract_opencv(${OPENCV_ARCHIVE_PATH} ${DOWNLOAD_DIR})
        build_opencv(${OPENCV_SRC} "core,imgcodecs")
    endif()

    set(OpenCV_DIR "${OPENCV_SRC}/build")
    file(GLOB OPENCV_LIBS "${OpenCV_DIR}/bin/Release/*.*")
    file(COPY ${OPENCV_LIBS} DESTINATION "${CMAKE_BINARY_DIR}/bin")
 
    find_package(OpenCV REQUIRED
	COMPONENTS core imgcodecs)

    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)

    set(PACK_LIB "${ProjectId}_lib")
    add_library(${PACK_LIB} STATIC ${ALL_SOURCE_FILES} )

    add_executable( ${ProjectId} ${ALL_SOURCE_FILES} )

    include_directories(${OpenCV_INCLUDE_DIRS})

    target_link_libraries(${ProjectId} ${PACK_LIB})
    target_link_libraries(${ProjectId} ${OpenCV_LIBS})
    target_link_libraries(${ProjectId} gtest gtest_main)

    set(TEST_IMG_DIR "${CMAKE_BINARY_DIR}/images")
    if(NOT EXISTS "${TEST_IMG_DIR}")
	file(MAKE_DIRECTORY "${TEST_IMG_DIR}")
	if(NOT EXISTS "${TEST_IMG_DIR}")
	    message(FATAL_ERROR "Failed to create directory for test images ${TEST_IMG_DIR}")
	endif()
    endif()

    enable_testing()
    add_test(NAME ${ProjectId} COMMAND ${ProjectId})

    if( UNIX )
        foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
            string(FIND ${SOURCE_FILE} ${PROJECT_BINARY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
            if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
                list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
            endif ()
        endforeach ()

        find_program(CPPCHECK cppcheck)
        add_custom_target(
                "${ProjectId}_cppcheck" ALL
                COMMAND ${CPPCHECK}
                --enable=warning,performance,portability,information,missingInclude
                --language=c++
                --std=c++11
                --error-exitcode=1
                --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
                --verbose
                --quiet
                ${ALL_SOURCE_FILES}
        )
    endif( UNIX )

    SET(ARGS_FOR_CHECK_COUNT_TESTS "")
    foreach (FILE_ELEM ${ALL_SOURCE_FILES})
        set(ARGS_FOR_CHECK_COUNT_TESTS "${ARGS_FOR_CHECK_COUNT_TESTS} ${FILE_ELEM}")
    endforeach ()

    add_custom_target("${ProjectId}_check_count_tests" ALL
            COMMAND "${Python3_EXECUTABLE}"
            ${CMAKE_SOURCE_DIR}/scripts/check_count_tests.py
            ${ProjectId}
            ${ARGS_FOR_CHECK_COUNT_TESTS}
    )
else( USE_SEQ )
    message( STATUS "-- ${ProjectId} - NOT BUILD!"  )
endif( USE_SEQ )
