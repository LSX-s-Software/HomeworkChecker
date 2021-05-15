//
//  DataManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#include "DataManager.hpp"

namespace DataManager {

std::hash<std::string> hashStr;

LoginError User::login(std::string email, std::string password) {
    LoginError error = LOGIN_SUCCESS;
    if (DBManager::connectDatabase()) {
        if (!DBManager::select("users", "id,password", "username='" + email + "'")) {
            if (DBManager::numRows() == 1) {
                MYSQL_ROW row = DBManager::fetchRow();
                if (row[1] == std::to_string(hashStr(password))) {
                    std::string idStr = row[0];
                    this->id = atoi(idStr.c_str());
                    this->email = email;
                    this->password = password;
                    this->type = 0;
                    error = LOGIN_SUCCESS;
                } else {
                    error = LOGIN_INVALID_PASSWOOD;
                }
            } else {
                error = LOGIN_INVALID_EMAIL;
            }
        } else {
            error = LOGIN_DATABASE_OPERATION_ERROR;
        }
    } else {
        error = LOGIN_CONNECTION_ERROR;
    }
    DBManager::closeConnection();
    return error;
}

RegisterError User::reg(std::string email, std::string password) {
    RegisterError error = REG_SUCCESS;
    if (DBManager::connectDatabase()) {
        if (!DBManager::select("users", "id", "username='" + email + "'")) {
            if (DBManager::numRows() == 0) {
                if (!DBManager::insert("users", "username,password", "'" + email + "','" + std::to_string(hashStr(password)) + "'")) {
                    if (DBManager::affectedRowCount() > 0) {
                        error = REG_SUCCESS;
                    } else {
                        error = REG_DATABASE_OPERATION_ERROR;
                    }
                } else {
                    error = REG_DATABASE_OPERATION_ERROR;
                }
            } else {
                error = REG_INVALID_EMAIL;
            }
        } else {
            error = REG_DATABASE_OPERATION_ERROR;
        }
    } else {
        error = REG_CONNECTION_ERROR;
    }
    DBManager::closeConnection();
    return error;
}
    
}
