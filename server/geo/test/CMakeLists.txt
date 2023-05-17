cmake_minimum_required(VERSION 3.9)

project("geo-test")

aux_source_directory(. GEO_TEST_SRCS)
aux_source_directory(.. GEO_TEST_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${GEO_TEST_SRCS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g -fprofile-arcs -ftest-coverage)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ..)

enable_testing()
target_link_libraries(${PROJECT_NAME} PRIVATE gcov)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
