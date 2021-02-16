cmake_minimum_required(VERSION 3.2)

project(ncc)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-DLOG_USE_COLOR")

add_executable(ncc_bin src/vec.c src/main.c log/src/log.c)
