cmake_minimum_required(VERSION 3.6)
project(RunAfterMultithreads)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILE_TYPE DEBUG)
SET(CMAKE_C_FLAGS_DEBUG "-g3 -Wall -lpthread")


set(SOURCE_FILES
    frame.cpp
    frame.h
    framegop.cpp
    framegop.h
    main.cpp
    threadpool.h
    utility.cpp
    utility.h)

add_executable(RunAfterMultithreads ${SOURCE_FILES})