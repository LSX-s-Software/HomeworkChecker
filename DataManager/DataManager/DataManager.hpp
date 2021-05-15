//
//  DataManager.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include "DBManager.hpp"

namespace DataManager {

typedef enum {
    LOGIN_SUCCESS,
    LOGIN_INVALID_EMAIL,
    LOGIN_INVALID_PASSWOOD,
    LOGIN_DATABASE_OPERATION_ERROR,
    LOGIN_CONNECTION_ERROR
} LoginError;

typedef enum {
    REG_SUCCESS,
    REG_INVALID_EMAIL,
    REG_DATABASE_OPERATION_ERROR,
    REG_CONNECTION_ERROR
} RegisterError;

class User {
    int id;
    std::string email;
    std::string password;
    int type;
    
public:
    LoginError login(std::string email, std::string password);
    RegisterError reg(std::string email, std::string password);
};

}

#endif /* DataManager_hpp */
