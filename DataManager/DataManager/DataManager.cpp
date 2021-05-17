//
//  DataManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#include "DataManager.hpp"

namespace DataManager {

std::hash<std::string> hashStr;

//MARK: - User类实现

DMError User::login(std::string email, std::string password) {
    DMError error = SUCCESS;
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
                    error = SUCCESS;
                } else {
                    error = INVALID_PASSWOOD;
                }
            } else {
                error = INVALID_EMAIL;
            }
        } else {
            error = DATABASE_OPERATION_ERROR;
        }
    } else {
        error = CONNECTION_ERROR;
    }
    DBManager::closeConnection();
    return error;
}

DMError User::reg(std::string email, std::string password) {
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        if (!DBManager::select("users", "id", "username='" + email + "'")) {
            if (DBManager::numRows() == 0) {
                if (!DBManager::insert("users", "username,password", "'" + email + "','" + std::to_string(hashStr(password)) + "'")) {
                    if (DBManager::affectedRowCount() > 0) {
                        error = SUCCESS;
                    } else {
                        error = DATABASE_OPERATION_ERROR;
                    }
                } else {
                    error = DATABASE_OPERATION_ERROR;
                }
            } else {
                error = INVALID_EMAIL;
            }
        } else {
            error = DATABASE_OPERATION_ERROR;
        }
    } else {
        error = CONNECTION_ERROR;
    }
    DBManager::closeConnection();
    return error;
}

//MARK: - Student类实现

DMError Student::setSchoolNum(std::string newNum) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("students", "school_num='" + newNum + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            schoolNum = newNum;
        else
            return DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Student::setClassId(long newClassId) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("students", "class_id='" + std::to_string(newClassId) + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            classId = newClassId;
        else
            return DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Student::setName(std::string newName) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("students", "name='" + newName + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            name = newName;
        else {
            DBManager::closeConnection();
            return DATABASE_OPERATION_ERROR;
        }
        DBManager::closeConnection();
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Student::reg(std::string schoolNum, std::string qq, std::string name) {
    if (DBManager::connectDatabase()) {
        int code = DBManager::select("students", "id", "school_num=" + schoolNum);
        if (!code) {
            if (DBManager::numRows() > 0) {
                DBManager::closeConnection();
                return TARGET_EXISTED;
            }
            code = DBManager::insert("students", "school_num,qq,name,register_time", "'" + schoolNum + "','" + qq + "','" + name + "',NOW()");
            if (!code && DBManager::affectedRowCount() > 0) {
                if (!DBManager::select("students", "id,register_time", "school_num='" + schoolNum + "'") && DBManager::numRows() == 1) {
                    MYSQL_ROW row = DBManager::fetchRow();
                    std::string idStr = row[0], timeStr = row[1];
                    id = atoi(idStr.c_str());
                    this->schoolNum = schoolNum;
                    this->qq = qq;
                    this->name = name;
                    register_time = atol(timeStr.c_str());
                } else {
                    DBManager::closeConnection();
                    return DATABASE_OPERATION_ERROR;
                }
            } else {
                DBManager::closeConnection();
                return DATABASE_OPERATION_ERROR;
            }
        } else {
            DBManager::closeConnection();
            return DATABASE_OPERATION_ERROR;
        }
        DBManager::closeConnection();
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<Student> getStudentList(long classId) {
    std::vector<Student> result;
    if (DBManager::connectDatabase()) {
        if (!DBManager::select("students", "*", "class_id=" + std::to_string(classId) + "")) {
            MYSQL_ROW row;
            while ((row = DBManager::fetchRow())) {
                std::string idStr = row[0], timeStr = row[5];
                result.push_back(Student(atoi(idStr.c_str()), row[1], row[2], classId, row[4], atol(timeStr.c_str())));
            }
        }
        DBManager::closeConnection();
    }
    return result;
}

Student getStudent(int id) {
    Student emptyResult;
    if (DBManager::connectDatabase()) {
        if (!DBManager::select("students", "*", "id=" + std::to_string(id)) && DBManager::numRows() > 0) {
            MYSQL_ROW row = DBManager::fetchRow();
            std::string classIdStr = (row[3] == NULL ? "0" : row[3]), timeStr = row[5];
            return Student(id, row[1], row[2], atoi(classIdStr.c_str()), row[4], atol(timeStr.c_str()));
        }
        DBManager::closeConnection();
    }
    return emptyResult;
}

//MARK: - Class类实现

DMError Class::setName(std::string newName) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("classes", "name='" + newName + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            name = newName;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Class::setLocation(std::string newLocation) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("classes", "location='" + newLocation + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            time = newLocation;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}
DMError Class::setTime(std::string newTime) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("classes", "location='" + newTime + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            time = newTime;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Class::setInviteCode(std::string newCode) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (newCode.length() != 4)
        return INVALID_ARGUMENT;
    if (DBManager::connectDatabase()) {
        int code = DBManager::select("classes", "id", "code='" + newCode + "'");
        if (!code) {
            if (DBManager::numRows() > 0) {
                DBManager::closeConnection();
                return TARGET_EXISTED;
            } else {
                code = DBManager::update("classes", "code='" + newCode + "'", "id=" + std::to_string(id));
                if (!code && DBManager::affectedRowCount() > 0) {
                    inviteCode = newCode;
                } else
                    error = DATABASE_OPERATION_ERROR;
            }
        } else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Class::endClass() {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("classes", "status=1", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            status = CLASS_ENDED;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Class::newClass(int teacherId, std::string name, std::string location, std::string time) {
    DMError error = SUCCESS;
    if (teacherId <= 0 || name.length() == 0)
        return INVALID_ARGUMENT;
    if (DBManager::connectDatabase()) {
        int code = DBManager::select("classes", "id", "teacher_id=" + std::to_string(teacherId) + " AND name='" + name + "'");
        if (!code) {
            if (DBManager::numRows() > 0) {
                error = TARGET_EXISTED;
            } else {
                code = DBManager::insert("classes", "teacher_id,name,location,time", std::to_string(teacherId) + ",'" + name + "','" + location + "','" + time + "'");
                if (!code && DBManager::affectedRowCount() > 0) {
                    if (!DBManager::select("classes", "id", "name='" + name + "'") && DBManager::numRows() == 1) {
                        MYSQL_ROW row = DBManager::fetchRow();
                        std::string idStr = row[0];
                        id = atol(idStr.c_str());
                        this->teacherId = teacherId;
                        this->name = name;
                        this->location = location;
                        this->time = time;
                        status = CLASS_RUNNING;
                    } else
                        error = DATABASE_OPERATION_ERROR;
                } else
                    error = DATABASE_OPERATION_ERROR;
            }
        } else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<Class> getClassList(int teacherId) {
    std::vector<Class> result;
    if (teacherId > 0 && DBManager::connectDatabase()) {
        if (!DBManager::select("classes", "*", "teacher_id=" + std::to_string(teacherId) + "")) {
            MYSQL_ROW row;
            while ((row = DBManager::fetchRow())) {
                std::string idStr = row[0], statusStr = row[6];
                result.push_back(Class(atol(idStr.c_str()), teacherId, row[2], (row[3]==NULL?"":row[3]), (row[4]==NULL?"":row[4]), row[5], (atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING)));
            }
        }
        DBManager::closeConnection();
    }
    return result;
}

Class getClass(long id) {
    Class emptyResult;
    if (id > 0 && DBManager::connectDatabase()) {
        if (!DBManager::select("classes", "*", "id=" + std::to_string(id)) && DBManager::numRows() > 0) {
            MYSQL_ROW row = DBManager::fetchRow();
            std::string teacherIdStr = row[1], statusStr = row[6];
            return Class(id, atoi(teacherIdStr.c_str()), row[2], row[3], row[4], row[5], (atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING));
        }
        DBManager::closeConnection();
    }
    return emptyResult;
}

Class getClass(std::string inviteCode) {
    Class emptyResult;
    if (inviteCode.length() == 4 && DBManager::connectDatabase()) {
        if (!DBManager::select("classes", "*", "code=" + inviteCode) && DBManager::numRows() > 0) {
            MYSQL_ROW row = DBManager::fetchRow();
            std::string idStr = row[0], teacherIdStr = row[1], statusStr = row[6];
            return Class(atol(idStr.c_str()), atoi(teacherIdStr.c_str()), row[2], row[3], row[4], inviteCode, (atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING));
        }
        DBManager::closeConnection();
    }
    return emptyResult;
}

DMError deleteClass(long id) {
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::remove("classes", "id=" + std::to_string(id));
        if (code || DBManager::affectedRowCount() == 0)
            error = DATABASE_OPERATION_ERROR;
        else {
            code = DBManager::update("students", "class_id=NULL", "class_id=" + std::to_string(id));
            if (code)
                error = DATABASE_OPERATION_ERROR;
        }
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

//MARK: - Homework类实现

DMError Homework::setContentURL(std::string newURL) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("homework", "content_url='" + newURL + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            contentURL = newURL;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Homework::setAttachmentURL(std::string newURL) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("homework", "attachment_url='" + newURL + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            attachmentURL = newURL;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Homework::setScore(unsigned short newScore) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("homework", "score=" + std::to_string(newScore), "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            score = newScore;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Homework::setComments(std::string newComments) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::update("homework", "comments='" + newComments + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            comments = newComments;
        else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Homework::newHomework(int studentId, long assignmentId, std::string contentURL, std::string attachmentURL) {
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId));
        if (!code) {
            if (DBManager::numRows() > 0)
                error = TARGET_EXISTED;
            else {
                code = DBManager::insert("homework", "student_id,assignment_id,content_url,attachment_url", std::to_string(studentId) + "," + std::to_string(assignmentId) + ",'" + contentURL + "','" + attachmentURL + "'");
                if (!code && DBManager::affectedRowCount() > 0) {
                    if (!DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId)) && DBManager::numRows() == 1) {
                        MYSQL_ROW row = DBManager::fetchRow();
                        std::string idStr = row[0];
                        id = atol(idStr.c_str());
                        this->studentId = studentId;
                        this->assignmentId = assignmentId;
                        this->contentURL = contentURL;
                        this->attachmentURL = attachmentURL;
                    } else
                        error = DATABASE_OPERATION_ERROR;
                } else
                    error = DATABASE_OPERATION_ERROR;
            }
        } else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMError Homework::review(unsigned short score, std::string comments) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMError error = SUCCESS;
    if (DBManager::connectDatabase()) {
        int code = DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId));
        if (!code) {
            if (DBManager::numRows() == 0)
                error = TARGET_NOT_FOUND;
            else {
                code = DBManager::update("homework", "score=" + std::to_string(score) + ",comments='" + comments + "'", "id=" + std::to_string(id));
                if (!code && DBManager::affectedRowCount() > 0) {
                    this->score = score;
                    this->comments = comments;
                } else
                    error = DATABASE_OPERATION_ERROR;
            }
        } else
            error = DATABASE_OPERATION_ERROR;
        DBManager::closeConnection();
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<Homework> getHomeworkListByStuId(int studentId) {
    std::vector<Homework> result;
    if (studentId > 0 && DBManager::connectDatabase()) {
        if (!DBManager::select("homework", "*", "student_id=" + std::to_string(studentId)) && DBManager::numRows() > 0) {
            MYSQL_ROW row;
            while ((row = DBManager::fetchRow())) {
                std::string idStr = row[0], assignmentIdStr = row[2], scoreStr = row[5];
                result.push_back(Homework(atol(idStr.c_str()), studentId, atol(assignmentIdStr.c_str()), row[3], (row[4]==NULL?"":row[4]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[6]));
            }
        }
        DBManager::closeConnection();
    }
    return result;
}

std::vector<Homework> getHomeworkListByAsmId(long assignmentId) {
    std::vector<Homework> result;
    if (assignmentId > 0 && DBManager::connectDatabase()) {
        if (!DBManager::select("homework", "*", "assignment_id=" + std::to_string(assignmentId)) && DBManager::numRows() > 0) {
            MYSQL_ROW row;
            while ((row = DBManager::fetchRow())) {
                std::string idStr = row[0], studentIdStr = row[1], scoreStr = row[5];
                result.push_back(Homework(atol(idStr.c_str()), atoi(studentIdStr.c_str()), assignmentId, row[3], (row[4]==NULL?"":row[4]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[6]));
            }
        }
        DBManager::closeConnection();
    }
    return result;
}

Homework getHomework(long id) {
    Homework emptyResult;
    if (id > 0 && DBManager::connectDatabase()) {
        if (!DBManager::select("homework", "*", "id=" + std::to_string(id)) && DBManager::numRows() > 0) {
            MYSQL_ROW row = DBManager::fetchRow();
            std::string studentIdStr = row[1], assignmentIdStr = row[2], scoreStr = row[5];
            return Homework(id, atoi(studentIdStr.c_str()), atol(assignmentIdStr.c_str()), row[3], (row[4]==NULL?"":row[4]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[6]);
        }
        DBManager::closeConnection();
    }
    return emptyResult;
}
    
}
