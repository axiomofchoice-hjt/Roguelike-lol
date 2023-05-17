cmake_minimum_required(VERSION 3.8)

project(geo VERSION 1.0)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} GEO_SRCS)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} ${GEO_SRCS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)

add_subdirectory(test)