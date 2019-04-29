cmake_minimum_required(VERSION 3.13)
project(parallel)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

find_package(Threads REQUIRED)

add_executable(parallel main.cpp graph.h fixtures.h sequential/sequential.h sequential/test.h openmp_bf/implementation.h openmp_bf/test.h pthread_bf/implementation.h pthread_bf/test.h test_correctness.h)

target_link_libraries(parallel hayai_main ${LIB_TIMING} Threads::Threads)
