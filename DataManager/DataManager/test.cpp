//
//  main.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include <iostream>
#include "DataManager.hpp"

int main(int argc, const char * argv[]) {
    DataManager::Student stu = DataManager::getStudent(1);
    std::cout << stu.getId() << stu.getName() << std::endl;
    
    return 0;
}
