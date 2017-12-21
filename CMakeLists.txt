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
project(libdop)
set(libdop_VERSION_MAJOR 1)
set(libdop_VERSION_MINOR 1)
set(libdop_VERSION_REVISION 2)

include_directories(BEFORE ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR}/src)

# Build
add_library(tinycsv STATIC
	src/tinycsv.c)

add_executable(tinycsv_info_print
    examples/info_print.c)

add_executable(tinycsv_print_as_csv
    examples/print_as_csv.c)

add_executable(tinycsv_replace_content
    examples/replace_content.c)

# Linking
target_link_libraries(tinycsv_info_print
    tinycsv)

target_link_libraries(tinycsv_print_as_csv
    tinycsv)

target_link_libraries(tinycsv_replace_content
    tinycsv)

# Install
install(TARGETS tinycsv ARCHIVE DESTINATION lib)
install_files("/include" .h
	${CMAKE_SOURCE_DIR}/src/tinycsv.h)

# Tests
#add_test(NAME hexdump COMMAND hexdump_test)
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
