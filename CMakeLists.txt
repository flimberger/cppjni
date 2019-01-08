cmake_minimum_required(VERSION 3.12)

project(cppjni CXX)

find_package(JNI REQUIRED)
find_package(Threads REQUIRED)

add_library(cppjni INTERFACE)
target_include_directories(cppjni
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(cppjni SYSTEM INTERFACE
    ${JNI_INCLUDE_DIRS})
target_link_libraries(cppjni INTERFACE Threads::Threads)
target_compile_features(cppjni INTERFACE cxx_std_17)

enable_testing()
add_subdirectory(test)
