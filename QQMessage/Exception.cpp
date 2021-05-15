#include "Exception.h"

WsConnectError::WsConnectError() : message("Websocket Connect Error") {}
WsConnectError::WsConnectError(std::string str) : message("Websocket Connect Error : " + str) {}