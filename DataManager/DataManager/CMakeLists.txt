cmake_minimum_required(VERSION 3.8)
project(DataManager)
set(CMAKE_BUILD_TYPE "Debug")
add_definitions(-std=c++17)
aux_source_directory(. DIR_SRCS)
link_directories(/usr/lib/x86_64-linux-gnu)
include_directories(
/usr/local/lib
/usr/include/mysql
)
add_library(DataManager STATIC ${DIR_SRCS})
target_link_libraries(DataManager libmysqlclient.so)
