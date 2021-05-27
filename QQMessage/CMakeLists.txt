cmake_minimum_required(VERSION 3.8)
project(QQMessage)
set(CMAKE_BUILD_TYPE "Debug")
add_definitions(-std=c++17)
aux_source_directory(. DIR_SRCS)
link_directories(
/usr/lib/x86_64-linux-gnu
../DataManager/DataManager/build
)
include_directories(
/usr/local/lib
/usr/include/mysql
../packages/asio/include
../packages/json
../packages/websocketpp/include
../DataManager/DataManager
)
add_library(QQMessage STATIC ${DIR_SRCS})
target_link_libraries(QQMessage libmysqlclient.so libDataManager.a)
