cmake_minimum_required(VERSION 3.9)

project("Roguelike-Server")

aux_source_directory(. DIR_SRCS)
aux_source_directory(async DIR_SRCS)
aux_source_directory(proto DIR_SRCS)
aux_source_directory(scene DIR_SRCS)
aux_source_directory(scene/action DIR_SRCS)
aux_source_directory(scene/env DIR_SRCS)
aux_source_directory(tools DIR_SRCS)

# set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${DIR_SRCS})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
find_package(glog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glog::glog)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
find_package(Protobuf CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::libprotobuf)
find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)

add_subdirectory(geo)
target_link_libraries(${PROJECT_NAME} PRIVATE geo)
