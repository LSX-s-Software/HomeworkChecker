//
//  DBManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#include "DBManager.hpp"
using namespace DBManager;

/// 连接数据库
/// @param account 数据库帐号
bool connectDatabase(DBAccount account) {
    mysql_init(&mysql); //初始化连接
    bool result = mysql_real_connect(&mysql, account.host.c_str(), account.username.c_str(), account.password.c_str(), "hw_assist", account.port, NULL, 0);
    if (result) {
        std::cout << "[INFO] [DBManager] MySQL connected" << std::endl;
        errMsg = "";
        return true;
    }
    else {
        errMsg = mysql_error(&mysql);
        std::cout << "[ERROR] [DBManager] MySQL connect failed: " << errMsg << std::endl;
        return false;
    }
}

/// 关闭数据库连接并释放查询结果使用的内存
void closeConnection() {
    if (queryResult != NULL)
        mysql_free_result(queryResult);  //释放一个结果集合使用的内存
    mysql_close(&mysql);
}

/// 查询数据库
/// @param queryString SQL语句
/// @returns code 错误代码（0=成功）
int query(std::string queryString) {
    int code = mysql_query(&mysql, queryString.c_str());
    if (code) {
        errMsg = mysql_error(&mysql);
        std::cout << "[ERROR] [DBManager] MySQL query failed: " << errMsg << std::endl;
    } else
        errMsg = "";
    return code;
}

int query(std::string queryString, DBActionType actionType) {
    std::string actionTypeStr;
    switch (actionType) {
        case DBManager::QUERY:
            actionTypeStr = "query";
            break;
        case DBManager::SELECT:
            actionTypeStr = "SELECT";
            break;
        case DBManager::INSERT:
            actionTypeStr = "INSERT";
            break;
        case DBManager::UPDATE:
            actionTypeStr = "UPDATE";
            break;
        case DBManager::DELETE:
            actionTypeStr = "DELETE";
            break;
        default:
            actionTypeStr = "query";
            break;
    }
    int code = mysql_query(&mysql, queryString.c_str());
    if (code) {
        errMsg = mysql_error(&mysql);
        std::cout << "[ERROR] [DBManager] MySQL " + actionTypeStr + " failed: " << errMsg << std::endl;
    } else
        errMsg = "";
    return code;
}

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
int select(std::string table, std::string columnNames) {
    return query("SELECT " + columnNames + " FROM " + table, DBManager::SELECT);
}

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
int select(std::string table, std::string columnNames, std::string conditions) {
    std::string queryStr = "SELECT " + columnNames + " FROM " + table + " WHERE " + conditions;
    return query(queryStr, DBManager::SELECT);
}

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
/// @param order 排序方式（SQL格式）
int select(std::string table, std::string columnNames, std::string conditions, std::string order) {
    std::string queryStr = "SELECT " + columnNames + " FROM " + table + " WHERE " + conditions + " ORDER BY " + order;
    return query(queryStr, DBManager::SELECT);
}

/// 插入数据
/// @param table 表名
/// @param columnNames 列名（以英文逗号分隔）
/// @param values 数据字符串（SQL格式）
int insert(std::string table, std::string columnNames, std::string values) {
    std::string queryStr = "INSERT INTO " + table + " (" + columnNames + ") VALUES (" + values + ")";
    return query(queryStr, DBManager::INSERT);
}

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
int update(std::string table, std::string columnAndValue) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue;
    return query(queryStr, DBManager::UPDATE);
}

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
/// @param conditions 条件（SQL格式）
int update(std::string table, std::string columnAndValue, std::string conditions) {
    std::string queryStr = "UPDATE " + table + " SET " + columnAndValue + " WHERE " + conditions;
    return query(queryStr, DBManager::UPDATE);
}

/// 删除数据
/// @param table 表名
/// @param conditions 匹配条件（SQL WHERE语句格式）
int remove(std::string table, std::string conditions) {
    std::string queryStr = "DELETE FROM " + table + " WHERE " + conditions;
    return query(queryStr, DBManager::DELETE);
}

unsigned long affectedRowCount() {
    return mysql_affected_rows(&mysql);
}
