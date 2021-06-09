//
//  DataManager.cpp
//  DataManager
//
//  Created by 林思行 on 2021/5/15.
//

#include "DataManager.hpp"

namespace DataManager {

bool connectDatabase() {
    int conStat = DBManager::checkConnection();
    if (conStat) {
#ifdef DEBUG
        if (conStat != -1)
            std::cout << "[INFO] [DataManager] SQL Server connection lost, reconncting..." << std::endl;
#endif
        DBManager::DBAccount remote;
        remote.host = "vps.coyangjr.cn";
        remote.username = "root";
        remote.password = "Whu2020";
        return DBManager::connectDatabase(remote);
    } else
        return true;
}

void disconnectDatabase() {
    DBManager::closeConnection();
}

//MARK: - User类实现

DMErrorType User::login(std::string email, std::string password) {
    email = DBManager::sqlInjectionCheck(email);
    if (connectDatabase()) {
        if (!DBManager::select("users", "id,password,name", "username='" + email + "'")) {
            if (DBManager::numRows() == 1) {
                MYSQL_ROW row = DBManager::fetchRow();
                if (row[1] == std::to_string(DMUtils::BKDRHash(password.c_str()))) {
                    std::string idStr = row[0];
                    this->id = atoi(idStr.c_str());
                    this->email = email;
                    this->password = password;
                    this->name = row[2];
                    this->type = 0;
                    return SUCCESS;
                } else {
                    return INVALID_PASSWOOD;
                }
            } else {
                return INVALID_EMAIL;
            }
        } else {
            return DATABASE_OPERATION_ERROR;
        }
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType User::reg(std::string email, std::string password) {
    email = DBManager::sqlInjectionCheck(email);
    if (connectDatabase()) {
        if (!DBManager::select("users", "id", "username='" + email + "'")) {
            if (DBManager::numRows() == 0) {
                if (!DBManager::insert("users", "username,password", "'" + email + "','" + std::to_string(DMUtils::BKDRHash(password.c_str())) + "'")) {
                    if (DBManager::affectedRowCount() > 0) {
                        return SUCCESS;
                    } else {
                        return DATABASE_OPERATION_ERROR;
                    }
                } else {
                    return DATABASE_OPERATION_ERROR;
                }
            } else {
                return INVALID_EMAIL;
            }
        } else {
            return DATABASE_OPERATION_ERROR;
        }
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType User::setName(std::string name) {
    name = DBManager::sqlInjectionCheck(name);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("users", "name='" + name + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            this->name = name;
        else
            code = -1;
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

//MARK: - Student类实现

Student::Student(int id) noexcept(false) {
    if (connectDatabase()) {
        if (!DBManager::select("students", "*", "id=" + std::to_string(id))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string classIdStr = (row[3] == NULL ? "0" : row[3]), timeStr = row[5];
                this->id = id;
                this->schoolNum = row[1];
                this->qq = row[2];
                this->classId = atol(classIdStr.c_str());
                this->name = row[4];
                this->registerTime = atol(timeStr.c_str());
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else {
        throw DMError(CONNECTION_ERROR);
    }
}

Student::Student(std::string qq) noexcept(false) {
    if (connectDatabase()) {
        if (!DBManager::select("students", "*", "qq='" + qq + "'")) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string idStr = row[0], classIdStr = (row[3] == NULL ? "0" : row[3]), timeStr = row[5];
                this->id = atoi(idStr.c_str());
                this->schoolNum = row[1];
                this->qq = qq;
                this->classId = atol(classIdStr.c_str());
                this->name = row[4];
                this->registerTime = atol(timeStr.c_str());
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType Student::setSchoolNum(std::string newNum) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("students", "school_num='" + newNum + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            schoolNum = newNum;
        else
            code = -1;
        return code == 0 ? SUCCESS : DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Student::setClassId(long newClassId) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("students", "class_id='" + std::to_string(newClassId) + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            classId = newClassId;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Student::setName(std::string newName) {
    newName = DBManager::sqlInjectionCheck(newName);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("students", "name='" + newName + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            name = newName;
            return SUCCESS;
        } else {
            return DATABASE_OPERATION_ERROR;
        }
    } else {
        return CONNECTION_ERROR;
    }
}

Student::Student(std::string schoolNum, std::string qq, std::string name) noexcept(false) {
    name = DBManager::sqlInjectionCheck(name);
    if (connectDatabase()) {
        int code = DBManager::select("students", "id", "school_num=" + schoolNum);
        if (!code) {
            if (DBManager::numRows() > 0)
                throw DMError(TARGET_EXISTED);
            code = DBManager::insert("students", "school_num,qq,name,register_time", "'" + schoolNum + "','" + qq + "','" + name + "',NOW()");
            if (!code && DBManager::affectedRowCount() > 0) {
                if (!DBManager::select("students", "id,register_time", "school_num='" + schoolNum + "'") && DBManager::numRows() == 1) {
                    MYSQL_ROW row = DBManager::fetchRow();
                    std::string idStr = row[0], timeStr = row[1];
                    id = atoi(idStr.c_str());
                    this->schoolNum = schoolNum;
                    this->qq = qq;
                    this->name = name;
                    registerTime = atol(timeStr.c_str());
                } else {
                    throw DMError(DATABASE_OPERATION_ERROR);
                }
            } else {
                throw DMError(DATABASE_OPERATION_ERROR);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

std::vector<Student> getStudentList(long classId) noexcept(false) {
    std::vector<Student> result;
    if (connectDatabase()) {
        if (!DBManager::select("students", "*", "class_id=" + std::to_string(classId) + "")) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row;
                while ((row = DBManager::fetchRow())) {
                    std::string idStr = row[0], timeStr = row[5];
                    result.push_back(Student(atoi(idStr.c_str()), row[1], row[2], classId, row[4], atol(timeStr.c_str())));
                }
            }
            return result;
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

//MARK: - Class类实现

Class::Class(long id) noexcept(false) {
    if (id <= 0)
        throw DMError(INVALID_ARGUMENT);
    if (connectDatabase()) {
        if (!DBManager::select("classes", "*", "id=" + std::to_string(id))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string teacherIdStr = row[1], statusStr = row[6];
                this->id = id;
                this->teacherId = atoi(teacherIdStr.c_str());
                this->name = row[2];
                this->location = row[3] == NULL ? "" : row[3];
                this->time = row[4] == NULL ? "" : row[4];
                this->inviteCode = row[5];
                this->status = atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING;
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

Class::Class(std::string inviteCode) noexcept(false) {
    if (inviteCode.length() != 4)
        throw DMError(INVALID_ARGUMENT);
    if (connectDatabase()) {
        if (!DBManager::select("classes", "*", "code='" + inviteCode + "'")) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string idStr = row[0], teacherIdStr = row[1], statusStr = row[6];
                this->id = atol(idStr.c_str());
                this->teacherId = atoi(teacherIdStr.c_str());
                this->name = row[2];
                this->location = row[3] == NULL ? "" : row[3];
                this->time = row[4] == NULL ? "" : row[4];
                this->inviteCode = inviteCode;
                this->status = atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING;
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType Class::setName(std::string newName) {
    newName = DBManager::sqlInjectionCheck(newName);
    if (id == -1)
        return OBJECT_NOT_INITED;
    DMErrorType error = SUCCESS;
    if (connectDatabase()) {
        int code = DBManager::update("classes", "name='" + newName + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0)
            name = newName;
        else
            error = DATABASE_OPERATION_ERROR;
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Class::setLocation(std::string newLocation) {
    newLocation = DBManager::sqlInjectionCheck(newLocation);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("classes", "location='" + newLocation + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            time = newLocation;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}
DMErrorType Class::setTime(std::string newTime) {
    newTime = DBManager::sqlInjectionCheck(newTime);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("classes", "location='" + newTime + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            time = newTime;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Class::setInviteCode(std::string newCode) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (newCode.length() != 4)
        return INVALID_ARGUMENT;
    if (connectDatabase()) {
        int code = DBManager::select("classes", "id", "status=0 AND code='" + newCode + "'");
        if (!code) {
            if (DBManager::numRows() > 0) {
                return TARGET_EXISTED;
            } else {
                code = DBManager::update("classes", "code='" + newCode + "'", "id=" + std::to_string(id));
                if (!code && DBManager::affectedRowCount() > 0) {
                    inviteCode = newCode;
                    return SUCCESS;
                } else
                    return DATABASE_OPERATION_ERROR;
            }
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Class::endClass() {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("classes", "status=1,code=''", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            status = CLASS_ENDED;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

Class::Class(int teacherId, std::string name, std::string location, std::string time) noexcept(false) {
    name = DBManager::sqlInjectionCheck(name);
    location = DBManager::sqlInjectionCheck(location);
    time = DBManager::sqlInjectionCheck(time);
    if (teacherId <= 0 || name.length() == 0)
        throw DMError(INVALID_ARGUMENT);
    if (connectDatabase()) {
        int code = DBManager::select("classes", "id", "teacher_id=" + std::to_string(teacherId) + " AND name='" + name + "'");
        if (!code) {
            if (DBManager::numRows() > 0) {
                throw DMError(TARGET_EXISTED);
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
                        throw DMError(DATABASE_OPERATION_ERROR);
                } else
                    throw DMError(DATABASE_OPERATION_ERROR);
            }
        } else
            throw DMError(DATABASE_OPERATION_ERROR);
    } else
        throw DMError(CONNECTION_ERROR);
}

std::vector<Class> getClassList(int teacherId) noexcept(false) {
    if (teacherId <= 0)
        throw DMError(INVALID_ARGUMENT);
    std::vector<Class> result;
    if (connectDatabase()) {
        if (!DBManager::select("classes", "*", "teacher_id=" + std::to_string(teacherId) + "")) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row;
                while ((row = DBManager::fetchRow())) {
                    std::string idStr = row[0], statusStr = row[6];
                    result.push_back(Class(atol(idStr.c_str()), teacherId, row[2], (row[3]==NULL?"":row[3]), (row[4]==NULL?"":row[4]), row[5], (atoi(statusStr.c_str()) ? CLASS_ENDED : CLASS_RUNNING)));
                }
            }
            return result;
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

int Class::getSize() noexcept(false) {
    if (id <= 0)
        return 0;
    if (connectDatabase()) {
        if (!DBManager::select("students", "count(*)", "class_id=" + std::to_string(id))) {
            int result = 0;
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string count = row[0];
                result = atoi(count.c_str());
            }
            return result;
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

long getTotalClassSize(int teacherId) noexcept(false) {
    if (teacherId <= 0)
        throw DMError(INVALID_ARGUMENT);
    long result = 0;
    if (connectDatabase()) {
        if (!DBManager::select("classes", "count(*)", "teacher_id=" + std::to_string(teacherId) + " AND status=0")) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string count = row[0];
                result = atol(count.c_str());
            }
            return result;
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType deleteClass(long id) {
    if (id <= 0)
        return INVALID_ARGUMENT;
    if (connectDatabase()) {
        int code = DBManager::remove("classes", "id=" + std::to_string(id));
        if (code)
            return DATABASE_OPERATION_ERROR;
        else {
            if (DBManager::affectedRowCount() == 0) {
                return TARGET_NOT_FOUND;
            } else {
                code = DBManager::update("students", "class_id=NULL", "class_id=" + std::to_string(id));
                if (code)
                    return DATABASE_OPERATION_ERROR;
                return SUCCESS;
            }
        }
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<ScoreListItem> getScoreList(long classId) noexcept(false) {
    if (classId <= 0)
        throw DMError(INVALID_ARGUMENT);
    std::vector<ScoreListItem> result;
    if (connectDatabase()) {
        try {
            std::vector<Student> stuList = getStudentList(classId);
            for (auto stu : stuList) {
                double sum = 0;
                std::vector<CompleteHomeworkList> homeworkList = getHomeworkListByStuId(stu.getId(), classId);
                for (auto hw : homeworkList) {
                    if (!hw.homework.isEmpty())
                        sum += hw.homework.getScore();
                }
                ScoreListItem item;
                item.stuId = stu.getId();
                item.name = stu.getName();
                item.schoolNum = stu.getSchoolNum();
                item.score = sum / homeworkList.size();
                result.push_back(item);
            }
            return result;
        } catch (...) {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

//MARK: - Homework类实现

Homework::Homework(long id) noexcept(false) {
    if (id <= 0)
        throw DMError(INVALID_ARGUMENT);
    if (connectDatabase()) {
        if (!DBManager::select("homework", "*", "id=" + std::to_string(id))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string studentIdStr = row[1], assignmentIdStr = row[2], scoreStr = row[5];
                this->id = id;
                this->studentId = atoi(studentIdStr.c_str());
                this->assignmentId = atol(assignmentIdStr.c_str());
                this->contentURL = row[3];
                this->attachmentURL = row[4] == NULL ? "" : row[4];
                this->score = static_cast<unsigned short>(atoi(scoreStr.c_str()));
                this->comments = row[6];
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

Homework::Homework(int studentId, long assignmentId) noexcept(false) {
    if (connectDatabase()) {
        int code = DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId));
        if (!code) {
            if (DBManager::numRows() > 0)
                throw DMError(TARGET_EXISTED);
            else {
                code = DBManager::insert("homework", "student_id,assignment_id,content_url,comments", std::to_string(studentId) + "," + std::to_string(assignmentId) + ",'',''");
                if (!code && DBManager::affectedRowCount() > 0) {
                    if (!DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId)) && DBManager::numRows() == 1) {
                        MYSQL_ROW row = DBManager::fetchRow();
                        std::string idStr = row[0];
                        id = atol(idStr.c_str());
                        this->studentId = studentId;
                        this->assignmentId = assignmentId;
                    } else
                        throw DMError(DATABASE_OPERATION_ERROR);
                } else
                    throw DMError(DATABASE_OPERATION_ERROR);
            }
        } else
            throw DMError(DATABASE_OPERATION_ERROR);
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType Homework::setContentURL(std::string newURL) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("homework", "content_url='" + newURL + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            contentURL = newURL;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Homework::setAttachmentURL(std::string newURL) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("homework", "attachment_url='" + newURL + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            attachmentURL = newURL;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Homework::setScore(unsigned short newScore) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("homework", "score=" + std::to_string(newScore), "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            score = newScore;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Homework::setComments(std::string newComments) {
    newComments = DBManager::sqlInjectionCheck(newComments);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("homework", "comments='" + newComments + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            comments = newComments;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Homework::submit(std::string contentURL, std::string attachmentURL) {
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        std::string updateStr = "content_url='" + contentURL + "'";
        updateStr += attachmentURL == "" ? "" : ",attachment_url='" + attachmentURL + "'";
        int code = DBManager::update("homework", updateStr, "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            this->contentURL = contentURL;
            this->attachmentURL = attachmentURL;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Homework::review(unsigned short score, std::string comments) {
    comments = DBManager::sqlInjectionCheck(comments);
    if (id == -1)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::select("homework", "id", "student_id=" + std::to_string(studentId) + " AND assignment_id=" + std::to_string(assignmentId));
        if (!code) {
            if (DBManager::numRows() == 0)
                return TARGET_NOT_FOUND;
            else {
                code = DBManager::update("homework", "score=" + std::to_string(score) + ",comments='" + comments + "'", "id=" + std::to_string(id));
                if (!code && DBManager::affectedRowCount() > 0) {
                    this->score = score;
                    this->comments = comments;
                    return SUCCESS;
                } else
                    return DATABASE_OPERATION_ERROR;
            }
        } else
            return DATABASE_OPERATION_ERROR;
    } else
        return CONNECTION_ERROR;
}

std::vector<Homework> getHomeworkListByAsmId(long assignmentId) noexcept(false) {
    if (assignmentId <= 0)
        throw DMError(INVALID_ARGUMENT);
    std::vector<Homework> result;
    if (connectDatabase()) {
        if (!DBManager::select("homework", "*", "assignment_id=" + std::to_string(assignmentId))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row;
                while ((row = DBManager::fetchRow())) {
                    std::string idStr = row[0], studentIdStr = row[1], scoreStr = row[5];
                    result.push_back(Homework(atol(idStr.c_str()), atoi(studentIdStr.c_str()), assignmentId, row[3], (row[4]==NULL?"":row[4]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[6]));
                }
            }
            return result;
        } else {
            return result;
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType deleteHomework(long id) {
    if (id <= 0)
        return INVALID_ARGUMENT;
    DMErrorType error = SUCCESS;
    if (connectDatabase()) {
        int code = DBManager::remove("homework", "id=" + std::to_string(id));
        if (code)
            error = DATABASE_OPERATION_ERROR;
        else {
            if (DBManager::affectedRowCount() == 0)
                error = TARGET_NOT_FOUND;
        }
        return error;
    } else {
        return CONNECTION_ERROR;
    }
}

//MARK: - Assignment类实现

Assignment::Assignment(unsigned int teacherId, std::string title, std::string description, long deadline, unsigned long classId) noexcept(false) {
    title = DBManager::sqlInjectionCheck(title);
    description = DBManager::sqlInjectionCheck(description);
    if (connectDatabase()) {
        int code = DBManager::insert("assignments", "teacher_id,title,description,start_date,deadline,class_id", std::to_string(teacherId) + ",'" + title + "','" + description + "',NOW()," + std::to_string(deadline) + "," + std::to_string(classId));
        if (!code && DBManager::affectedRowCount() > 0) {
            if (!DBManager::select("assignments", "id", "teacher_id=" + std::to_string(teacherId), "start_time DESC LIMIT 1") && DBManager::numRows() == 1) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string idStr = row[0];
                id = atol(idStr.c_str());
            } else
                throw DMError(DATABASE_OPERATION_ERROR);
        } else
            throw DMError(DATABASE_OPERATION_ERROR);
    } else {
        throw DMError(CONNECTION_ERROR);
    }
}

Assignment::Assignment(unsigned long id) noexcept(false) {
    if (id <= 0)
        throw DMError(INVALID_ARGUMENT);
    if (connectDatabase()) {
        if (!DBManager::select("assignments", "id,teacher_id,title,description,unix_timestamp(start_date),unix_timestamp(deadline),class_id", "id=" + std::to_string(id))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row = DBManager::fetchRow();
                std::string teacherIdStr = row[1], startTimeStr = row[4], ddlStr = row[5], classIdStr = row[6];
                this->id = id;
                this->teacherId = atoi(teacherIdStr.c_str());
                this->title = row[2];
                this->description = row[3];
                this->startTime = atol(startTimeStr.c_str());
                this->deadline = atol(ddlStr.c_str());
                this->classId = atol(classIdStr.c_str());
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}

DMErrorType Assignment::setTitle(std::string title) {
    title = DBManager::sqlInjectionCheck(title);
    if (id == 0)
        return OBJECT_NOT_INITED;
    if (title.length() > 80)
        return INVALID_ARGUMENT;
    if (connectDatabase()) {
        int code = DBManager::update("assignments", "title='" + title + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            this->title = title;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}
DMErrorType Assignment::setDescription(std::string description) {
    description = DBManager::sqlInjectionCheck(description);
    if (id == 0)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("assignments", "description='" + description + "'", "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            this->description = description;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

DMErrorType Assignment::setDeadline(long time) {
    if (id == 0)
        return OBJECT_NOT_INITED;
    if (connectDatabase()) {
        int code = DBManager::update("assignments", "deadline=" + std::to_string(time), "id=" + std::to_string(id));
        if (!code && DBManager::affectedRowCount() > 0) {
            this->deadline = time;
            return SUCCESS;
        } else
            return DATABASE_OPERATION_ERROR;
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<Assignment> getAssignmentList(unsigned int teacherId) noexcept(false) {
    std::vector<Assignment> result;
    if (teacherId > 0 && connectDatabase()) {
        if (!DBManager::select("assignments", "id,teacher_id,title,description,unix_timestamp(start_date),unix_timestamp(deadline),class_id", "teacher_id=" + std::to_string(teacherId))) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row;
                while ((row = DBManager::fetchRow())) {
                    std::string idStr = row[0], startTimeStr = row[4], ddlStr = row[5], classIdStr = row[6];
                    result.push_back(Assignment(atol(idStr.c_str()), teacherId, row[2], row[3], atol(startTimeStr.c_str()), atol(ddlStr.c_str()), atol(classIdStr.c_str())));
                }
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else {
        throw DMError(CONNECTION_ERROR);
    }
    return result;
}

DMErrorType deleteAssignment(unsigned long id, bool (* handler)(std::vector<Homework>)) {
    if (connectDatabase()) {
        int code = DBManager::remove("assignments", "id=" + std::to_string(id));
        if (code || DBManager::affectedRowCount() == 0)
            return DATABASE_OPERATION_ERROR;
        else {
            if (handler != NULL) {
                std::vector<Homework> result;
                if (!DBManager::select("homework", "*", "assignment_id=" + std::to_string(id)) && DBManager::numRows() > 0) {
                    MYSQL_ROW row;
                    while ((row = DBManager::fetchRow())) {
                        std::string idStr = row[0], studentIdStr = row[1], scoreStr = row[5];
                        result.push_back(Homework(atol(idStr.c_str()), atoi(studentIdStr.c_str()), id, row[3], (row[4]==NULL?"":row[4]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[6]));
                    }
                    handler(result);
                }
            }
            if (DBManager::remove("homework", "assignment_id=" + std::to_string(id)))
                return DATABASE_OPERATION_ERROR;
            return SUCCESS;
        }
    } else {
        return CONNECTION_ERROR;
    }
}

std::vector<CompleteHomeworkList> getHomeworkListByStuId(int studentId, long classId) noexcept(false) {
    if (studentId <= 0 || classId <= 0)
        throw DMError(INVALID_ARGUMENT);
    std::vector<CompleteHomeworkList> result;
    if (connectDatabase()) {
        std::string queryStr = "SELECT * FROM (SELECT id,teacher_id,title,description,unix_timestamp(start_date),unix_timestamp(deadline),class_id FROM assignments WHERE class_id=" + std::to_string(classId) + ") AS ass_list LEFT JOIN homework ON homework.student_id=" + std::to_string(studentId) + " AND homework.assignment_id=ass_list.id";
        if (!DBManager::query(queryStr)) {
            if (DBManager::numRows() > 0) {
                MYSQL_ROW row;
                while ((row = DBManager::fetchRow())) {
                    CompleteHomeworkList item;
                    std::string idStr = row[0], teacherIdStr = row[1], startTimeStr = row[4], ddlStr = row[5], classIdStr = row[6];
                    item.assignment = Assignment(atol(idStr.c_str()), atoi(teacherIdStr.c_str()), row[2], row[3], atol(startTimeStr.c_str()), atol(ddlStr.c_str()), atol(classIdStr.c_str()));
                    if (row[7] != NULL) {
                        std::string idStr = row[7], assignmentIdStr = row[9], scoreStr = row[12];
                        item.homework = Homework(atol(idStr.c_str()), studentId, atol(assignmentIdStr.c_str()), row[10], (row[11]==NULL?"":row[11]), static_cast<unsigned short>(atoi(scoreStr.c_str())), row[13]);
                    } else {
                        std::string assIdStr = row[0];
                        item.homework = Homework(-1, studentId, atol(assIdStr.c_str()), "", "", 0, "");
                    }
                    result.push_back(item);
                }
                return result;
            } else {
                throw DMError(TARGET_NOT_FOUND);
            }
        } else {
            throw DMError(DATABASE_OPERATION_ERROR);
        }
    } else
        throw DMError(CONNECTION_ERROR);
}
    
}
