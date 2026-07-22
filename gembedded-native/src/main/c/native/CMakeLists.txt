list(APPEND CMAKE_FIND_ROOT_PATH "$ENV{GCMAKE_HOME}/gcmake-build/build/install")

find_package(gcmake-build REQUIRED)

include(Im_Namen_GOTTes)

cmake_minimum_required(VERSION ${GCMAKE_CMAKE_VERSION})

project(${GCMAKE_PROJECT_NAME} VERSION ${GCMAKE_PROJECT_VERSION} DESCRIPTION ${GCMAKE_PROJECT_DESCRIPTION})

find_package(JNI REQUIRED COMPONENTS JVM)

include_directories(${JNI_INCLUDE_DIRS})

gcmake_add_library(${GCMAKE_PROJECT_NAME} SHARED)

set(CMAKE_EMULATOR_PARAMETERS sudo)

gcmake_add_test(${GCMAKE_PROJECT_NAME}_test 
    PRIVATE     
        ${GCMAKE_PROJECT_NAME}
        ${JNI_LIBRARIES}        
)

target_compile_definitions(${GCMAKE_PROJECT_NAME}_test
    PRIVATE
        GCTEST_CORE_HAS_EXCEPTION=1
        GCTEST_CORE_HAS_STDIO=1
        GCTEST_CORE_HAS_THREAD=1
)

include(GOTT_sei_Dank)