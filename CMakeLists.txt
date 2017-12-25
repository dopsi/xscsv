# The MIT License (MIT)
#
# Copyright (c) 2017 Simon Doppler
#
# Permission is hereby granted, free of charge, to any person obtaining a 
# copy of this software and associated documentation files (the 
# "Software"), to deal in the Software without restriction, including 
# without limitation the rights to use, copy, modify, merge, publish, 
# distribute, sublicense, and/or sell copies of the Software, and to 
# permit persons to whom the Software is furnished to do so, subject to 
# the following conditions:
#
# The above copyright notice and this permission notice shall be included 
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

cmake_minimum_required(VERSION 2.6)
# Check for out-of-source build
if( CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR AND NOT MSVC_IDE )
	message(FATAL_ERROR "In-source builds are not allowed.
	Please create a directory and run cmake from there, passing the path
	to this source directory as the last argument.
	This process created the file `CMakeCache.txt' and the directory `CMakeFiles'.
	Please delete them.")
endif()

enable_testing()

# Set project data
project(xscsv)
set(libdop_VERSION_MAJOR 0)
set(libdop_VERSION_MINOR 1)
set(libdop_VERSION_REVISION 0)

include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)

# Build
add_library(xscsv STATIC
	src/xscsv.c)

add_executable(xscsv_info_print
    examples/info_print.c)

add_executable(xscsv_info_print_tab
    examples/info_print_tab.c)

add_executable(xscsv_print_as_csv
    examples/print_as_csv.c)

add_executable(xscsv_replace_content
    examples/replace_content.c)

add_executable(xscsv_new_document
    examples/new_document.c)

## Test executables

add_executable(xscsv_test_lines
    tests/test_lines.c)

add_executable(xscsv_test_columns
    tests/test_columns.c)

add_executable(xscsv_test_columns_in_line
    tests/test_columns_in_line.c)

add_executable(xscsv_test_get_contents
    tests/test_get_contents.c)

add_executable(xscsv_test_tab_lines
    tests/test_tab_lines.c)

add_executable(xscsv_test_tab_columns
    tests/test_tab_columns.c)

add_executable(xscsv_test_tab_columns_in_line
    tests/test_tab_columns_in_line.c)

add_executable(xscsv_test_tab_get_contents
    tests/test_tab_get_contents.c)

# Linking
target_link_libraries(xscsv_info_print
    xscsv)

target_link_libraries(xscsv_info_print_tab
    xscsv)

target_link_libraries(xscsv_print_as_csv
    xscsv)

target_link_libraries(xscsv_replace_content
    xscsv)

target_link_libraries(xscsv_new_document
    xscsv)

## Test executables

target_link_libraries(xscsv_test_lines
    xscsv)

target_link_libraries(xscsv_test_columns
    xscsv)

target_link_libraries(xscsv_test_columns_in_line
    xscsv)

target_link_libraries(xscsv_test_get_contents
    xscsv)

target_link_libraries(xscsv_test_tab_lines
    xscsv)

target_link_libraries(xscsv_test_tab_columns
    xscsv)

target_link_libraries(xscsv_test_tab_columns_in_line
    xscsv)

target_link_libraries(xscsv_test_tab_get_contents
    xscsv)

# Install
install(TARGETS xscsv ARCHIVE DESTINATION lib)
install_files("/include" .h
	${CMAKE_SOURCE_DIR}/src/xscsv.h)

# Tests
add_test(NAME xscsv_lines COMMAND xscsv_test_lines ${CMAKE_SOURCE_DIR}/tests/res/example.csv)
add_test(NAME xscsv_columns COMMAND xscsv_test_columns ${CMAKE_SOURCE_DIR}/tests/res/example.csv)
add_test(NAME xscsv_columns_in_line COMMAND xscsv_test_columns_in_line ${CMAKE_SOURCE_DIR}/tests/res/example.csv)
add_test(NAME xscsv_get_contents COMMAND xscsv_test_get_contents ${CMAKE_SOURCE_DIR}/tests/res/example.csv)

add_test(NAME xscsv_tab_lines COMMAND xscsv_test_tab_lines ${CMAKE_SOURCE_DIR}/tests/res/example.tsv)
add_test(NAME xscsv_tab_columns COMMAND xscsv_test_tab_columns ${CMAKE_SOURCE_DIR}/tests/res/example.tsv)
add_test(NAME xscsv_tab_columns_in_line COMMAND xscsv_test_tab_columns_in_line ${CMAKE_SOURCE_DIR}/tests/res/example.tsv)
add_test(NAME xscsv_tab_get_contents COMMAND xscsv_test_tab_get_contents ${CMAKE_SOURCE_DIR}/tests/res/example.tsv)
#add_test(NAME buffer COMMAND buffer_test)
#add_test(NAME djb2_hash_on_string COMMAND hash_djb2_test)
#add_test(NAME rot13_chicken COMMAND rot13_test)
#add_test(NAME dmath_max COMMAND dmath_max_test)
#add_test(NAME dmath_mean COMMAND dmath_mean_test)
#add_test(NAME dmath_median COMMAND dmath_median_test)
#add_test(NAME dmath_min COMMAND dmath_min_test)
#add_test(NAME dmath_range COMMAND dmath_range_test)
#add_test(NAME dmath_standart_deviation COMMAND dmath_standart_deviation_test)
#add_test(NAME dmath_sum COMMAND dmath_sum_test)
#add_test(NAME dmath_variance COMMAND dmath_variance_test)
