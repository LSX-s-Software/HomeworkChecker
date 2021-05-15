//
//  DBManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include "DBManager.hpp"
#include <iostream>

#define DEBUG

namespace DBManager {

MYSQL* mysql = NULL;
MYSQL_RES* queryResult = NULL;
std::string errMsg = "";

/// 连接数据库
/// @param account 数据库帐号
bool connectDatabase(DBAccount account) {
    mysql = mysql_init(NULL); //初始化连接
    mysql = mysql_real_connect(mysql, account.host.c_str(), account.username.c_str(), account.password.c_str(), "homework_checker", account.port, NULL, 0);
    if (mysql) {
#ifdef DEBUG
        std::cout << "[INFO] [DBManager] MySQL connected, conectionPtr=" << mysql << std::endl;
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

/// 使用默认账号密码连接数据库
bool connectDatabase() {
    DBManager::DBAccount account;
    account.username = "root";
    account.password = "gh8rv_aGdd";
    return connectDatabase(account);
}

/// 关闭数据库连接并释放查询结果使用的内存
void closeConnection() {
    if (queryResult != NULL)
        mysql_free_result(queryResult);  //释放一个结果集合使用的内存
    queryResult = NULL;
    mysql_close(mysql);
#ifdef DEBUG
    std::cout << "[INFO] [DBManager] MySQL disconnected" << std::endl;
#endif
}

/// 查询数据库
/// @param queryString SQL语句
/// @returns code 错误代码（0=成功）
int query(std::string queryString) {
#ifdef DEBUG
    std::cout << "[LOG] [DBManager] queryStr: " << queryString << std::endl;
#endif
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
        case DELETE:
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

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
int select(std::string table, std::string columnNames) {
    return query("SELECT " + columnNames + " FROM " + table, SELECT);
}

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
int select(std::string table, std::string columnNames, std::string conditions) {
    std::string queryStr = "SELECT " + columnNames + " FROM " + table + " WHERE " + conditions;
    return query(queryStr, SELECT);
}

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
/// @param order 排序方式（SQL格式）
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

/// 获取结果的下一行，等于mysql_fetch_row
MYSQL_ROW fetchRow() {
    if (!queryResult)
        return NULL;
    return mysql_fetch_row(queryResult);
}

/// 插入数据
/// @param table 表名
/// @param columnNames 列名（以英文逗号分隔）
/// @param values 数据字符串（SQL格式）
int insert(std::string table, std::string columnNames, std::string values) {
    std::string queryStr = "INSERT INTO " + table + " (" + columnNames + ") VALUES (" + values + ")";
    return query(queryStr, INSERT);
}

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
int update(std::string table, std::string columnAndValue) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue;
    return query(queryStr, UPDATE);
}

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
/// @param conditions 条件（SQL格式）
int update(std::string table, std::string columnAndValue, std::string conditions) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue + " WHERE " + conditions;
    return query(queryStr, UPDATE);
}

/// 删除数据
/// @param table 表名
/// @param conditions 匹配条件（SQL WHERE语句格式）
int remove(std::string table, std::string conditions) {
    std::string queryStr = "DELETE FROM " + table + " WHERE " + conditions;
    return query(queryStr, DELETE);
}

unsigned long affectedRowCount() {
    return mysql_affected_rows(mysql);
}

}
