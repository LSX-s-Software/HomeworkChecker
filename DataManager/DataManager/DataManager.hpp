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
    TARGET_NOT_FOUND,
    DATABASE_OPERATION_ERROR,
    CONNECTION_ERROR,
    INVALID_ARGUMENT,
    OBJECT_NOT_INITED
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
    Student(std::string schoolNum, std::string qq, std::string name) throw(DMError);
    
    bool isEmpty() {
        return id == -1;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的get接口
    
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
};

/// 获取学生列表
/// @param classId 班级ID
std::vector<Student> getStudentList(int classId);

/// 获取学生
/// @param id 学生ID
Student getStudent(int id);

/// 获取学生
/// @param qq 学生ID
Student getStudent(std::string qq) throw(DMError);

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
    Class(int teacherId, std::string name, std::string location, std::string time) throw(DMError);
    
    bool isEmpty() {
        return id == -1;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的get接口
    
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
};

/// 获取班级列表
/// @param teacherId 教师ID
std::vector<Class> getClassList(int teacherId);

/// 获取班级
/// @param id 班级ID
Class getClass(long id);

/// 获取班级
/// @param inviteCode 邀请码
Class getClass(std::string inviteCode);

/// 删除班级
/// @param id 班级ID
DMError deleteClass(long id);

//MARK: - Homework类定义

class Homework {
    long id;
    int studentId;
    long assignmentId;
    std::string contentURL;
    std::string attachmentURL;
    unsigned short score;
    std::string comments;
    
public:
    Homework() {
        id = -1;
    }
    Homework(long id, int studentId, long assignmentId, std::string contentURL, std::string attachmentURL, unsigned short score, std::string comments) {
        this->id = id;
        this->studentId = studentId;
        this->assignmentId = assignmentId;
        this->contentURL = contentURL;
        this->attachmentURL = attachmentURL;
        this->score = score;
        this->comments = comments;
    }
    
    /// 创建作业提交记录
    /// @param studentId 学生ID
    /// @param assignmentId 布置的作业ID
    Homework(int studentId, long assignmentId) throw(DMError);
    
    bool isEmpty() {
        return id == -1;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的get接口
    
    long getId() {
        return id;
    }
    int getStudentId() {
        return studentId;
    }
    long getAssignmentId() {
        return assignmentId;
    }
    std::string getContentURL() {
        return contentURL;
    }
    std::string getAttachmentURL() {
        return attachmentURL;
    }
    unsigned short getScore() {
        return score;
    }
    std::string getComments() {
        return comments;
    }
    
    DMError setContentURL(std::string newURL);
    DMError setAttachmentURL(std::string newURL);
    DMError setScore(unsigned short newScore);
    DMError setComments(std::string newComments);
    
    //MARK: Other Operations
    
    /// 提交正文和附件
    /// @param contentURL 正文URL
    /// @param attachmentURL 附件URL
    DMError submit(std::string contentURL, std::string attachmentURL);
    
    /// 作业打分
    /// @param score 分数
    /// @param comments 评语
    DMError review(unsigned short score, std::string comments);
};

/// 获取某个学生提交的作业列表
/// @param studentId 学生ID
std::vector<Homework> getHomeworkListByStuId(int studentId);

/// 按布置的作业ID来获取作业列表
/// @param assignmentId 布置的作业ID
std::vector<Homework> getHomeworkListByAsmId(long assignmentId);

/// 获取作业
/// @param id 作业ID
Homework getHomework(long id);

//MARK: - Assignment类定义

class Assignment {
    unsigned long id;
    unsigned int teacherId;
    std::string title;
    std::string description;
    long startTime;
    long deadline;
    unsigned long classId;
    
public:
    Assignment() {
        id = 0;
    }
    Assignment(unsigned long id, unsigned int teacherId, std::string title, std::string description, long startTime, long deadline, unsigned long classId) {
        this->id = id;
        this->teacherId = teacherId;
        this->title = title;
        this->description = description;
        this->startTime = startTime;
        this->deadline = deadline;
        this->classId = classId;
    }
    /// 创建作业
    /// @param teacherId 教师ID
    /// @param title 标题
    /// @param description 描述
    /// @param deadline 截止时间
    /// @param classId 班级ID
    Assignment(unsigned int teacherId, std::string title, std::string description, long deadline, unsigned long classId) throw(DMError);
    
    bool isEmpty() {
        return id == 0;
    }
    
    //MARK: Getters & Setters
    //WARNING: 不要在调用默认构造函数之后直接调用以下的get接口
    
    unsigned long getId() {
        return id;
    }
    unsigned int getTeacherId() {
        return teacherId;
    }
    std::string getTitle() {
        return title;
    }
    std::string getDescription() {
        return description;
    }
    long getStartTime() {
        return startTime;
    }
    long getDeadline() {
        return deadline;
    }
    unsigned long getClassId() {
        return classId;
    }
    
    DMError setTitle(std::string title);
    DMError setDescription(std::string description);
    DMError setDeadline(long time);
};

/// 获取作业列表
/// @param teacherId 教师ID
std::vector<Assignment> getAssignmentList(unsigned int teacherId) throw(DMError);

/// 删除布置的作业，同时从数据库移除提交到该任务的所有作业记录
/// @param id 布置的作业ID
/// @param handler 接受提交的作业列表的函数
DMError deleteAssignment(unsigned long id, bool (* handler)(std::vector<Homework>) = NULL);

}

#endif /* DataManager_hpp */
