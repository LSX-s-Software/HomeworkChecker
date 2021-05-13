//
//  DBManager.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#ifndef DBManager_hpp
#define DBManager_hpp

#include <iostream>
#include <string>

#include "mysql.h"

namespace DBManager {

typedef struct DBAccount {
    std::string host = "localhost";
    int port = 3306;
    std::string username;
    std::string password;
} DBAccount;

typedef enum DBActionType {
    QUERY,
    SELECT,
    INSERT,
    UPDATE,
    DELETE
} DBActionType;

MYSQL mysql;
MYSQL_RES* queryResult = NULL;
std::string errMsg = "";

bool connectDatabase(DBAccount account);
void closeConnection();
int query(std::string queryString);
int select(std::string table, std::string columnNames);
int select(std::string table, std::string columnNames, std::string conditions);
int select(std::string table, std::string columnNames, std::string conditions, std::string order);
int insert(std::string table, std::string columnNames, std::string values);
int update(std::string table, std::string columnAndValue);
int update(std::string table, std::string columnAndValue, std::string conditions);
int remove(std::string table, std::string conditions);
unsigned long affectedRowCount();

}

#endif /* DBManager_hpp */
