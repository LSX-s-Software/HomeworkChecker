//
//  DBManager.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/13.
//

#ifndef DBManager_hpp
#define DBManager_hpp
#pragma GCC visibility push(default)

#include <string>

#include "mysql.h"

/*
 定义DEBUG宏可让DBManager将错误输出至控制台
 定义VERBOSE宏可让DBManager将完整的调试数据输出至控制台
 */

#ifndef DEBUG
#define DEBUG
#endif
//#ifndef VERBOSE
//#define VERBOSE
//#endif

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
    DEL
} DBActionType;

/// 连接数据库
/// @param account 数据库帐号
bool connectDatabase(DBAccount account);

/// 关闭数据库连接并释放查询结果使用的内存
void closeConnection();

/// 检查数据库连接是否仍然可用，如果可用，返回0
int checkConnection();

/// 查询数据库
/// @param queryString SQL语句
/// @returns code 错误代码（0=成功）
int query(std::string queryString);

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
int select(std::string table, std::string columnNames);

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
int select(std::string table, std::string columnNames, std::string conditions);

/// 获取数据
/// @param table 表名
/// @param columnNames 列名（SQL格式）
/// @param conditions 条件（SQL格式）
/// @param order 排序方式（SQL格式）
int select(std::string table, std::string columnNames, std::string conditions, std::string order);

/// SELECT操作结果的行数
unsigned long numRows();

/// 获取结果的下一行，等于mysql_fetch_row
MYSQL_ROW fetchRow();

/// 插入数据
/// @param table 表名
/// @param columnNames 列名（以英文逗号分隔）
/// @param values 数据字符串（SQL格式）
int insert(std::string table, std::string columnNames, std::string values);

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
int update(std::string table, std::string columnAndValue);

/// 更新数据
/// @param table 表名
/// @param columnAndValue 列名-值（SQL格式）
/// @param conditions 条件（SQL格式）
int update(std::string table, std::string columnAndValue, std::string conditions);

/// 删除数据
/// @param table 表名
/// @param conditions 匹配条件（SQL WHERE语句格式）
int remove(std::string table, std::string conditions);

/// INSERT、UPDATE、DELETE操作影响的行数
unsigned long affectedRowCount();

/// SQL注入检查
/// @param str 要检查的字符串
std::string sqlInjectionCheck(std::string str);

}

#pragma GCC visibility pop

#endif /* DBManager_hpp */
