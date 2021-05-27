#pragma once
#include <json.hpp>
#include <iostream>
#include <string>

class PrivateMessageGetter
{
private:
    long long time;
    long long senderId;

    std::string rawData;


public:
    PrivateMessageGetter(nlohmann::json decode) :
        senderId(decode.at("user_id").get<long long>()),time(decode.at("time").get<long long>()), rawData(decode.at("message").get<std::string>())
    { }

    std::string getRawData()
    {
        return rawData;
    }

    long long getSenderId()
    {
        return senderId;
    }
};

