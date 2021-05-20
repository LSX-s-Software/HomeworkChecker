//
//  DMError.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/19.
//

#include "DMError.hpp"

namespace DataManager {

    DMError::DMError(DMErrorType error) {
        switch (error) {
        case SUCCESS:
            break;
        case INVALID_EMAIL:
            throw DMExcetion::INVALID_EMAIL();
            break;
        case INVALID_PASSWOOD:
            throw DMExcetion::INVALID_PASSWOOD();
            break;
        case TARGET_EXISTED:
            throw DMExcetion::TARGET_EXISTED();
            break;
        case TARGET_NOT_FOUND:
            throw DMExcetion::TARGET_NOT_FOUND();
            break;
        case DATABASE_OPERATION_ERROR:
            throw DMExcetion::DATABASE_OPERATION_ERROR();
            break;
        case CONNECTION_ERROR:
            throw DMExcetion::CONNECTION_ERROR();
            break;
        case INVALID_ARGUMENT:
            throw DMExcetion::INVALID_ARGUMENT();
            break;
        case OBJECT_NOT_INITED:
            throw DMExcetion::OBJECT_NOT_INITED();
            break;
        default:
            throw DMExcetion::UNKOWN_ERROR();
            break;
        }
    }

}
