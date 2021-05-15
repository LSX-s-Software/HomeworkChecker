#pragma once
#include <exception>
#include <string>

class WsConnectError : public std::exception
{
public:
    WsConnectError();
    WsConnectError(std::string str);
    virtual ~WsConnectError() {}

    virtual const char* what() const throw ()
    {
        return message.c_str();
    }

private:
    std::string message;
};