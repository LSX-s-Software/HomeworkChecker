#pragma once
#include <exception>
#include <string>
/// <summary>
/// ws连接错误
/// </summary>
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

/// <summary>
/// 文件操作错误
/// </summary>
class FileError : public std::exception
{
public:
    FileError();
    FileError(std::string str);
    virtual ~FileError() {}

    virtual const char* what() const throw ()
    {
        return message.c_str();
    }

private:
    std::string message;
};

/// <summary>
/// 文件不存在
/// </summary>
class FileNotExist : public std::exception
{
public:
    FileNotExist();
    FileNotExist(std::string str);
    virtual ~FileNotExist() {}

    virtual const char* what() const throw ()
    {
        return message.c_str();
    }

private:
    std::string message;
};