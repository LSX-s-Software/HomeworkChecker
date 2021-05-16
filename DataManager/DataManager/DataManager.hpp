//
//  DataManager.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include "DBManager.hpp"
#include <vector>

namespace DataManager {

//MARK: - User类定义

typedef enum {
    SUCCESS,
    INVALID_EMAIL,
    INVALID_PASSWOOD,
    TARGET_EXISTED,
    DATABASE_OPERATION_ERROR,
    CONNECTION_ERROR,
    ARGUMENT_ERROR
} DMError;

class User {
    int id;
    std::string email;
    std::string password;
    int type;
    
public:
    DMError login(std::string email, std::string password);
    DMError reg(std::string email, std::string password);
};

//MARK: - Student类定义

class Student {
    int id;
    std::string schoolNum;
    std::string qq;
    long classId;
    std::string name;
    long register_time;
    
public:
    Student() {
        id = -1;
    }
    Student(int id, std::string schoolNum, std::string qq, long classId, std::string name, long registerTime) {
        this->id = id;
        this->schoolNum = schoolNum;
        this->qq = qq;
        this->classId = classId;
        this->name = name;
        this->register_time = registerTime;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的接口
    
    int getId() {
        return id;
    }
    std::string getSchoolNum() {
        return schoolNum;
    }
    std::string getQQ() {
        return qq;
    }
    long getClassId() {
        return classId;
    }
    std::string getName() {
        return name;
    }
    long getRegTime() {
        return register_time;
    }
    
    DMError setSchoolNum(std::string newNum);
    DMError setClassId(long newClassId);
    DMError setName(std::string newName);
    
    //MARK: Other Operations
    
    /// 学生注册
    DMError reg(std::string schoolNum, std::string qq, std::string name);
};

//MARK: - Class类定义

typedef enum {
    CLASS_RUNNING,
    CLASS_ENDED
} ClassStatus;

class Class {
    long id;
    int teacherId;
    std::string name;
    std::string location;
    std::string time;
    std::string inviteCode;
    ClassStatus status;
    
public:
    Class() {
        id = -1;
    }
    Class(long id, int teacherId, std::string name, std::string location, std::string time, std::string inviteCode, ClassStatus status) {
        this->id = id;
        this->teacherId = teacherId;
        this->name = name;
        this->location = location;
        this->time = time;
        this->inviteCode = inviteCode;
        this->status = status;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的接口
    
    long getId() {
        return id;
    }
    std::string getName() {
        return name;
    }
    std::string getLocation() {
        return location;
    }
    std::string getTime() {
        return time;
    }
    std::string getInviteCode() {
        return inviteCode;
    }
    ClassStatus getStatus() {
        return status;
    }
    
    DMError setName(std::string newName);
    DMError setLocation(std::string newLocation);
    DMError setTime(std::string newTime);
    DMError setInviteCode(std::string newCode);
    DMError endClass();
    
    //MARK: Other Operations
    
    /// 新增班级
    DMError newClass(int teacherId, std::string name, std::string location, std::string time);
};

//MARK: 数据库操作

std::vector<Student> getStudentList(int classId);
Student getStudent(int id);
std::vector<Class> getClassList(int teacherId);
Class getClass(long id);
Class getClass(std::string inviteCode);
DMError deleteClass(long id);

}

#endif /* DataManager_hpp */
