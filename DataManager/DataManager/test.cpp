//
//  main.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include <iostream>
#include "DataManager.hpp"

int main(int argc, const char * argv[]) {
    DataManager::User me;
    std::cout << me.reg("123456", "123456") << std::endl;
    std::cout << me.login("123456", "123456") << std::endl;
    
    return 0;
}
