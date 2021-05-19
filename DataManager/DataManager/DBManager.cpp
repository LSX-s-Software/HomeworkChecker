//
//  DBManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include "DBManager.hpp"
#include <iostream>

#ifndef DEBUG
#define DEBUG
    #ifndef VERBOSE
    #define VERBOSE
    #endif
#endif

namespace DBManager {

MYSQL* mysql = NULL;
MYSQL_RES* queryResult = NULL;
std::string errMsg = "";

bool connectDatabase(DBAccount account) {
    mysql = mysql_init(NULL); //初始化连接
    mysql = mysql_real_connect(mysql, account.host.c_str(), account.username.c_str(), account.password.c_str(), "homework_checker", account.port, NULL, 0);
    if (mysql) {
#ifdef VERBOSE
        std::cout << "[INFO] [DBManager] MySQL connected." << std::endl;
#endif
        errMsg = "";
        return true;
    }
    else {
        errMsg = mysql_error(mysql);
#ifdef DEBUG
        std::cout << "[ERROR] [DBManager] MySQL connect failed: " << errMsg << std::endl;
#endif
        return false;
    }
}

bool connectDatabase() {
    DBManager::DBAccount account;
    account.username = "root";
    account.password = "gh8rv_aGdd";
    return connectDatabase(account);
}

void closeConnection() {
    if (queryResult != NULL)
        mysql_free_result(queryResult);  //释放一个结果集合使用的内存
    queryResult = NULL;
    mysql_close(mysql);
#ifdef VERBOSE
    std::cout << "[INFO] [DBManager] MySQL disconnected." << std::endl;
#endif
}

int query(std::string queryString) {
    if (!mysql) {
#ifdef DEBUG
        std::cout << "[ERROR] [DBManager] MySQL is not connected: " << errMsg << std::endl;
#endif
        return -1;
    }
#ifdef DEBUG
    std::cout << "[LOG] [DBManager] queryStr: \"" << queryString << "\"" << std::endl;
#endif
    if (queryResult != NULL) {
        mysql_free_result(queryResult);
        queryResult = NULL;
    }
    int code = mysql_query(mysql, queryString.c_str());
    if (code) {
        errMsg = mysql_error(mysql);
#ifdef DEBUG
        std::cout << "[ERROR] [DBManager] MySQL query failed: " << errMsg << std::endl;
#endif
    } else {
        errMsg = "";
        queryResult = mysql_store_result(mysql);
    }
    return code;
}

int query(std::string queryString, DBActionType actionType) {
    if (!mysql) {
#ifdef DEBUG
        std::cout << "[ERROR] [DBManager] MySQL is not connected: " << errMsg << std::endl;
#endif
        return -1;
    }
#ifdef DEBUG
    std::cout << "[LOG] [DBManager] queryStr: \"" << queryString << "\"" << std::endl;
#endif
    if (queryResult != NULL) {
        mysql_free_result(queryResult);
        queryResult = NULL;
    }
    std::string actionTypeStr;
    switch (actionType) {
        case QUERY:
            actionTypeStr = "query";
            break;
        case SELECT:
            actionTypeStr = "SELECT";
            break;
        case INSERT:
            actionTypeStr = "INSERT";
            break;
        case UPDATE:
            actionTypeStr = "UPDATE";
            break;
        case DEL:
            actionTypeStr = "DELETE";
            break;
        default:
            actionTypeStr = "query";
            break;
    }
    int code = mysql_query(mysql, queryString.c_str());
    if (code) {
        errMsg = mysql_error(mysql);
#ifdef DEBUG
        std::cout << "[ERROR] [DBManager] MySQL " + actionTypeStr + " failed: " << errMsg << std::endl;
#endif
    } else {
        errMsg = "";
        queryResult = mysql_store_result(mysql);
    }
    return code;
}

int select(std::string table, std::string columnNames) {
    return query("SELECT " + columnNames + " FROM " + table, SELECT);
}

int select(std::string table, std::string columnNames, std::string conditions) {
    std::string queryStr = "SELECT " + columnNames + " FROM " + table + " WHERE " + conditions;
    return query(queryStr, SELECT);
}

int select(std::string table, std::string columnNames, std::string conditions, std::string order) {
    std::string queryStr = "SELECT " + columnNames + " FROM " + table + " WHERE " + conditions + " ORDER BY " + order;
    return query(queryStr, SELECT);
}

unsigned long numRows() {
    if (queryResult == NULL) {
        return 0;
    }
    return mysql_num_rows(queryResult);
}

MYSQL_ROW fetchRow() {
    if (!queryResult)
        return NULL;
    return mysql_fetch_row(queryResult);
}

int insert(std::string table, std::string columnNames, std::string values) {
    std::string queryStr = "INSERT INTO " + table + " (" + columnNames + ") VALUES (" + values + ")";
    return query(queryStr, INSERT);
}

int update(std::string table, std::string columnAndValue) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue;
    return query(queryStr, UPDATE);
}

int update(std::string table, std::string columnAndValue, std::string conditions) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue + " WHERE " + conditions;
    return query(queryStr, UPDATE);
}

int remove(std::string table, std::string conditions) {
    std::string queryStr = "DELETE FROM " + table + " WHERE " + conditions;
    return query(queryStr, DEL);
}

unsigned long affectedRowCount() {
    return mysql_affected_rows(mysql);
}

}
