#pragma once
#include <exception>
#include <string>
/// <summary>
/// ws���Ӵ���
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
/// �ļ���������
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
/// �ļ�������
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