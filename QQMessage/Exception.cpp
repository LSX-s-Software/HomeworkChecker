#include "Exception.h"

WsConnectError::WsConnectError() : message("Websocket Connect Error") {}
WsConnectError::WsConnectError(std::string str) : message("Websocket Connect Error : " + str) {}

FileError::FileError() : message("File Error") {}
FileError::FileError(std::string str) : message("File Error : " + str) {}

FileNotExist::FileNotExist() : message("File Error") {}
FileNotExist::FileNotExist(std::string str) : message("File Error : " + str) {}