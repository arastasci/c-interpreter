cmake_minimum_required(VERSION 3.24)
project(cmpe230p1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cmpe230p1
        main.c
        token.c
        token.h)
