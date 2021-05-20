//
//  DMError.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/19.
//

#ifndef DMError_hpp
#define DMError_hpp

#include <exception>
#include <string>

namespace DataManager {

typedef enum {
    SUCCESS,
    INVALID_EMAIL,
    INVALID_PASSWOOD,
    TARGET_EXISTED,
    TARGET_NOT_FOUND,
    DATABASE_OPERATION_ERROR,
    CONNECTION_ERROR,
    INVALID_ARGUMENT,
    OBJECT_NOT_INITED
} DMErrorType;

class DMError: public std::exception {
    DMErrorType error;
    std::string message;
    std::string help;
    
public:
    DMError() {
        message = "Unknown Error";
    }
    DMError(DMErrorType error);
    virtual const char* what() const throw () {
        return message.c_str();
    }
};

}

#endif /* DMError_hpp */
