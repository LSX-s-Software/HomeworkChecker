//
//  DMError.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/19.
//

#include "DMError.hpp"

namespace DataManager {

DMError::DMError(DMErrorType error) {
    this->error = error;
    switch (error) {
        case SUCCESS:
            message = "Success";
            break;
        case INVALID_EMAIL:
            message = "Invalid Email";
            break;
        case INVALID_PASSWOOD:
            message = "Invalid Password";
            break;
        case TARGET_EXISTED:
            message = "Target Existed";
            break;
        case TARGET_NOT_FOUND:
            message = "Target Not Found";
            break;
        case DATABASE_OPERATION_ERROR:
            message = "Database Operation Error";
            help = "Refer to console log to get more information.";
            break;
        case CONNECTION_ERROR:
            message = "Database Connection Error";
            help = "Check network conection and server state.";
            break;
        case INVALID_ARGUMENT:
            message = "Invalid Argument";
            break;
        case OBJECT_NOT_INITED:
            message = "Object Not inited";
            help = "Attempting to invoke setters before the object is fully inited.";
            break;
        default:
            message = "Unknown Error";
            break;
    }
}

}
