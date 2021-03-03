cmake_minimum_required(VERSION 3.2)

project(ncc)

# set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-DLOG_USE_COLOR -ftrapv")

if (DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DDEBUG")
endif()

add_executable(ncc_bin src/main.c src/utils/hashmap.c src/utils/vec.c src/utils/panic.c)
add_library(log STATIC deps/log/src/log.c)
target_link_libraries(ncc_bin log m)

target_include_directories(ncc_bin PUBLIC deps/log/src)

enable_testing()
add_test(NAME vector-basic-ops COMMAND ncc_bin "vector")
add_test(NAME hashmap-readwrite-small COMMAND ncc_bin "hashmap" 10)
add_test(NAME hashmap-readwrite-medium COMMAND ncc_bin "hashmap" 500)
add_test(NAME hashmap-readwrite-large COMMAND ncc_bin "hashmap" 10000)
add_test(NAME panic-test COMMAND bash -c "if ncc_bin 'this should cause a panic'; then exit 1; fi; exit 0")
