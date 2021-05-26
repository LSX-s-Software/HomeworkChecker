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

    class DMError : public std::exception
    {
    public:
        DMError() : message("Error.") {}
        DMError(DMErrorType error);
        DMError(std::string str) : message("Error : " + str) {}
        ~DMError() throw () {
        }

        virtual const char* what() const throw () {
            return message.c_str();
        }

    private:
        std::string message;
    };

    namespace DMException
    {
        class INVALID_EMAIL : public DMError
        {
        public:
            INVALID_EMAIL() : message("Invalid Email.") {}
            INVALID_EMAIL(std::string str) : message("Error : " + str) {}
            ~INVALID_EMAIL() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class INVALID_PASSWOOD : public DMError
        {
        public:
            INVALID_PASSWOOD() : message("Invalid Password.") {}
            INVALID_PASSWOOD(std::string str) : message("Error : " + str) {}
            ~INVALID_PASSWOOD() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class TARGET_EXISTED : public DMError
        {
        public:
            TARGET_EXISTED() : message("Target Existed.") {}
            TARGET_EXISTED(std::string str) : message("Error : " + str) {}
            ~TARGET_EXISTED() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class TARGET_NOT_FOUND : public DMError
        {
        public:
            TARGET_NOT_FOUND() : message("Target Not Found.") {}
            TARGET_NOT_FOUND(std::string str) : message("Error : " + str) {}
            ~TARGET_NOT_FOUND() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class DATABASE_OPERATION_ERROR : public DMError
        {
        public:
            DATABASE_OPERATION_ERROR() : message("Database Operation Error. Refer to console log to get more information.") {}
            DATABASE_OPERATION_ERROR(std::string str) : message("Error : " + str) {}
            ~DATABASE_OPERATION_ERROR() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class CONNECTION_ERROR : public DMError
        {
        public:
            CONNECTION_ERROR() : message("Database Connection Error. Check network conection and server state.") {}
            CONNECTION_ERROR(std::string str) : message("Error : " + str) {}
            ~CONNECTION_ERROR() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class INVALID_ARGUMENT : public DMError
        {
        public:
            INVALID_ARGUMENT() : message("Invalid Argument.") {}
            INVALID_ARGUMENT(std::string str) : message("Error : " + str) {}
            ~INVALID_ARGUMENT() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class OBJECT_NOT_INITED : public DMError
        {
        public:
            OBJECT_NOT_INITED() : message("Object Not inited. Attempting to invoke setters before the object is fully inited.") {}
            OBJECT_NOT_INITED(std::string str) : message("Error : " + str) {}
            ~OBJECT_NOT_INITED() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };

        class UNKOWN_ERROR : public DMError
        {
        public:
            UNKOWN_ERROR() : message("Unkown Error.") {}
            UNKOWN_ERROR(std::string str) : message("Error : " + str) {}
            ~UNKOWN_ERROR() throw () {
            }

            virtual const char* what() const throw () {
                return message.c_str();
            }

        private:
            std::string message;
        };
    };

}

#endif /* DMError_hpp */
