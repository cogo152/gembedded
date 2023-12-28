find_package(gcmake-build CONFIG 1.0.6 REQUIRED)

include(Gcmake_Begin)

cmake_minimum_required(VERSION ${GCMAKE_CMAKE_VERSION})

project(${GCMAKE_PROJECT_NAME} VERSION ${GCMAKE_PROJECT_VERSION} DESCRIPTION ${GCMAKE_PROJECT_DESCRIPTION})

find_package(JNI REQUIRED)

include_directories(${JNI_INCLUDE_DIRS})

gcmake_add_library(${GCMAKE_PROJECT_NAME} SHARED)

gcmake_add_test(${GCMAKE_PROJECT_NAME}_test 
    PRIVATE     
        ${GCMAKE_PROJECT_NAME}
        ${JNI_LIBRARIES}        
)

include(Gcmake_End)