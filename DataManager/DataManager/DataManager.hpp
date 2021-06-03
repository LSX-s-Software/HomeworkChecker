//
//  DataManager.hpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#ifndef DataManager_hpp
#define DataManager_hpp
#pragma GCC visibility push(default)

#include "DBManager.hpp"
#include "DMError.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace DMUtils {

/// BKDR Hash Function
unsigned int BKDRHash(char *str);

std::string double2FixedStr(double num, unsigned fix);

}

namespace DataManager {

bool connectDatabase();
void disconnectDatabase();

//MARK: - User类定义

class User {
    int id;
    std::string email;
    std::string password;
    std::string name;
    int type;
    
public:
    User() {
        id = -1;
    }
    
    DMErrorType login(std::string email, std::string password);
    DMErrorType reg(std::string email, std::string password);
    
    int getId() {
        return id;
    }
    std::string getName() {
        return name;
    }
    DMErrorType setName(std::string name);
    
};

//MARK: - Student类定义

class Student {
    int id;
    std::string schoolNum;
    std::string qq;
    long classId;
    std::string name;
    long registerTime;
    
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
        this->registerTime = registerTime;
    }
    /// 获取学生
    /// @param id 学生ID
    Student(int id) noexcept(false);
    /// 获取学生
    /// @param qq 学生ID
    Student(std::string qq) noexcept(false);
    /// 学生注册
    /// @param schoolNum 学号
    /// @param qq QQ号
    /// @param name 姓名
    Student(std::string schoolNum, std::string qq, std::string name) noexcept(false);
    
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
        return registerTime;
    }
    
    DMErrorType setSchoolNum(std::string newNum);
    DMErrorType setClassId(long newClassId);
    DMErrorType setName(std::string newName);
};

/// 获取学生列表
/// @param classId 班级ID
std::vector<Student> getStudentList(long classId) noexcept(false);

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
    /// 获取班级
    /// @param id 班级ID
    Class(long id) noexcept(false);
    /// 获取班级
    /// @param inviteCode 邀请码
    Class(std::string inviteCode) noexcept(false);
    /// 新建班级
    /// @param teacherId 教师ID
    /// @param name 名称
    /// @param location 上课地点
    /// @param time 上课时间
    Class(int teacherId, std::string name, std::string location, std::string time) noexcept(false);
    
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
    int getSize() noexcept(false);
    
    DMErrorType setName(std::string newName);
    DMErrorType setLocation(std::string newLocation);
    DMErrorType setTime(std::string newTime);
    DMErrorType setInviteCode(std::string newCode);
    DMErrorType endClass();
};

/// 获取班级列表
/// @param teacherId 教师ID
std::vector<Class> getClassList(int teacherId) noexcept(false);

/// 获取总学生人数
/// @param teacherId 教师ID
long getTotalClassSize(int teacherId) noexcept(false);

/// 删除班级
/// @param id 班级ID
DMErrorType deleteClass(long id);

typedef struct {
    int stuId;
    std::string name;
    std::string schoolNum;
    float score;
} ScoreListItem;

/// 获取班级的分数列表
/// @param classId 班级ID
std::vector<ScoreListItem> getScoreList(long classId) noexcept(false);

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
        score = 0;
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
    /// 获取作业
    /// @param id 作业ID
    Homework(long id) noexcept(false);
    /// 创建作业提交记录
    /// @param studentId 学生ID
    /// @param assignmentId 布置的作业ID
    Homework(int studentId, long assignmentId) noexcept(false);
    
    bool isEmpty() {
        return id == -1;
    }
    
    /// 获取作业状态（0=未提交，1=已提交未批改，2=已批改）
    int getStatus() {
        if (id == -1)
            return 0;
        else if (score > 0)
            return 2;
        else
            return 1;
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
    
    DMErrorType setContentURL(std::string newURL);
    DMErrorType setAttachmentURL(std::string newURL);
    DMErrorType setScore(unsigned short newScore);
    DMErrorType setComments(std::string newComments);
    
    //MARK: Other Operations
    
    /// 提交正文和附件
    /// @param contentURL 正文URL
    /// @param attachmentURL 附件URL
    DMErrorType submit(std::string contentURL, std::string attachmentURL);
    
    /// 作业打分
    /// @param score 分数
    /// @param comments 评语
    DMErrorType review(unsigned short score, std::string comments);
};

/// 按布置的作业ID来获取作业列表
/// @param assignmentId 布置的作业ID
std::vector<Homework> getHomeworkListByAsmId(long assignmentId) noexcept(false);

/// 删除提交记录
/// @param id 提交的作业ID
DMErrorType deleteHomework(long id);

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
    /// 获取布置的作业
    /// @param id ID
    Assignment(unsigned long id) noexcept(false);
    /// 创建作业
    /// @param teacherId 教师ID
    /// @param title 标题
    /// @param description 描述
    /// @param deadline 截止时间
    /// @param classId 班级ID
    Assignment(unsigned int teacherId, std::string title, std::string description, long deadline, unsigned long classId) noexcept(false);
    
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
    
    DMErrorType setTitle(std::string title);
    DMErrorType setDescription(std::string description);
    DMErrorType setDeadline(long time);
};

/// 获取布置的作业列表
/// @param teacherId 教师ID
std::vector<Assignment> getAssignmentList(unsigned int teacherId) noexcept(false);

typedef struct {
    Assignment assignment;
    Homework homework;
} CompleteHomeworkList;

/// 获取某个学生的作业列表
/// @param studentId 学生ID
/// @param classId 学生所在班级的ID（增加这一项是为了减少一次数据库的查询）
std::vector<CompleteHomeworkList> getHomeworkListByStuId(int studentId, long classId) noexcept(false);

/// 删除布置的作业，同时从数据库移除提交到该任务的所有作业记录
/// @param id 布置的作业ID
/// @param handler 接受提交的作业列表的函数
DMErrorType deleteAssignment(unsigned long id, bool (* handler)(std::vector<Homework>) = NULL);

}

#pragma GCC visibility pop
#endif /* DataManager_hpp */
