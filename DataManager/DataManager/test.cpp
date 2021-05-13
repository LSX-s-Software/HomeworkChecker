//
//  main.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include <iostream>
#include "DBManager.hpp"

int main(int argc, const char * argv[]) {
    DBManager::DBAccount account;
    account.username = "root";
    account.password = "gh8rv_aGdd";
    DBManager::connectDatabase(account);
    return 0;
}
