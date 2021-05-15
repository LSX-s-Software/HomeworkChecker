#include <iostream>
#include <string>
#include <json.hpp>
using namespace std;

#include "QQMessage.h"

int main()
{
    try
    {
        QQMessage::_Init("127.0.0.1:6700");
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }
    
    string x;
    while (cin >> x)
    {}
    QQMessage::_Stop();
    return 0;
}