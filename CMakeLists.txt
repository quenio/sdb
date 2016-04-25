cmake_minimum_required(VERSION 3.5)
project(sdb)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c packed_structs.h file_header.h file_header.c commands.c commands.h db_file.c db_file.h)
add_executable(sdb ${SOURCE_FILES})