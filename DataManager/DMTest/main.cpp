//
//  main.cpp
//  DMTest
//
//  Created by 林思行 on 2021/6/4.
//

#include <iostream>
#include "../DataManager/DataManager.hpp"

int main(int argc, const char * argv[]) {
    DataManager::connectDatabase();
    DataManager::disconnectDatabase();
    std::cout << "Connection Test Completed." << std::endl;
    return 0;
}
