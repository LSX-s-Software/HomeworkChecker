cmake_minimum_required(VERSION 3.8)
project(HomeworkCheckerServer)
set(CMAKE_BUILD_TYPE "Debug")
add_definitions(-std=c++17)
aux_source_directory(. DIR_SRCS)
link_directories(
/usr/lib/x86_64-linux-gnu
../DataManager/DataManager/build
../QQMessage/build
)
include_directories(
/usr/local/lib
/usr/include/mysql
../packages/asio/include
../packages/json
../packages/websocketpp/include
../DataManager/DataManager
../QQMessage
)
add_executable(HomeworkCheckerServer ${DIR_SRCS})
target_link_libraries(HomeworkCheckerServer libQQMessage.a libDataManager.a libmysqlclient.so pthread)
