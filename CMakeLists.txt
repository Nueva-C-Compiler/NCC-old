cmake_minimum_required(VERSION 3.2)

project(ncc)

# set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-DLOG_USE_COLOR")

if (DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG")
endif()

add_executable(ncc_bin src/main.c src/utils/hashmap.c src/utils/vec.c)
add_library(log STATIC deps/log/src/log.c)
target_link_libraries(ncc_bin log m)

target_include_directories(ncc_bin PUBLIC deps/log/src)

enable_testing()
add_test(NAME run-exec COMMAND ncc_bin)
