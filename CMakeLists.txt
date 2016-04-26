cmake_minimum_required(VERSION 3.5)
project(sdb)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES packed_structs.h file_header.h file_header.c commands.c commands.h db_file.c db_file.h str.c str.h)
add_executable(sdb main.c ${SOURCE_FILES})

set(MIN_UNIT_FILES min_unit.c min_unit.h)
add_executable(str_tests str_tests.c ${MIN_UNIT_FILES} ${SOURCE_FILES})
