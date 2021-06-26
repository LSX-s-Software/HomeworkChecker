# 图形用户界面

## 整体功能
为了提升软件的易用性，我们为教师端提供了图形用户界面。教师端所有操作均可在图形化界面中完成。

## 项目结构

### 引用
- Qt *(第三方库)*

### 整体构成

```
HomeworkCheckerGUI
├─ ClassPage.qml  “班级”页面
├─ DateRectangle.qml  日期选择器
├─ GeneralPage.qml  “总览”页面
├─ InfoOfClass.qml  班级信息
├─ InfoOfTask.qml  作业信息
├─ LaunchScreen.qml  启动页
├─ LoginPage.qml  登录页
├─ MarkPage.qml  “成绩”页面
├─ NewAClass.qml  新建班级
├─ NewAssignment.qml  新建作业
├─ RegPage.qml  注册页
├─ SettingPage.qml  “设置”页面
├─ TaskPage.qml  “作业”页面
├─ WebsocketClientForApp.cpp
├─ WebsocketClientForApp.h
├─ account.cpp
├─ account.h  全局帐号管理
├─ classscoreviewcontroller.cpp
├─ classscoreviewcontroller.h  班级分数页面控制器
├─ classviewcontroller.cpp
├─ classviewcontroller.h  ”班级“页面控制器
├─ correctHomework.qml  批改作业
├─ correcthomework.cpp
├─ correcthomework.h  批改页面控制器
├─ generalviewcontroller.cpp
├─ generalviewcontroller.h  ”总览“页面控制器
├─ infooftask.cpp
├─ infooftask.h  作业详情页面控制器
├─ main.cpp  启动函数
├─ main.qml  主窗口
├─ qml.qrc  qml资源配置文件
├─ scoreWithClass.qml  班级成绩
├─ scoreWithStudent.qml  学生成绩
├─ setting.config
├─ settingpage.cpp
├─ settingpage.h  ”设置“页面控制器
├─ studentscoreviewcontroller.cpp
├─ studentscoreviewcontroller.h  学生成绩页面控制器
├─ taskpage.cpp
├─ taskpage.h  ”作业“页面控制器
```



## 关键技术

为了配合C++来制作图形界面，我们选用了Qt Quick框架。每个页面对应一个Qml文件。

Qml负责呈现页面，而页面的功能需要通过qml内嵌的js调用C++的函数来实现。

### 编写Qml可调用的自定义C++类

以Account类为例：

```c++
#include <QObject>
#include <QString>
#include <QDebug>
#include "qqml.h"
#include "DataManager.hpp"

class Account: public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ getId CONSTANT)
    Q_PROPERTY(QString userName READ getName WRITE setName)
    QML_ELEMENT
public:
    explicit Account(QObject *parent = nullptr);
    Q_INVOKABLE int reg(QString userName, QString password);
    Q_INVOKABLE int login(QString userName, QString password);
    Q_INVOKABLE bool connectDB();
    static int getId();
    static QString getName();
    static void setName(const QString &name);
    
private:
    static DataManager::User user;
};
```



### 注册自定义C++类

在Qt App引擎启动之前使用以下的方法注册自定义C++类（视图控制器）：

```c++
//自定义CPP模块
qmlRegisterType<GeneralViewController>("GeneralVC",1,0,"GeneralVC");
qmlRegisterType<Account>("Account",1,0,"Account");
qmlRegisterType<SettingPage>("MySettingPage", 1, 0, "MySettingPage");
qmlRegisterType<ClassViewController>("ClassVC", 1, 0, "ClassVC");
qmlRegisterType<TaskPage>("AssignmentVC", 1, 0, "AssignmentVC");
qmlRegisterType<InfoOfTask>("HomeworkVC", 1, 0, "HomeworkVC");
qmlRegisterType<ClassScoreViewController>("ClassScoreVC", 1, 0, "ClassScoreVC");
qmlRegisterType<StudentScoreViewController>("StudentScoreVC", 1, 0, "StudentScoreVC");
qmlRegisterType<CorrectHomework>("HomeworkInfoVC", 1, 0, "HomeworkInfoVC");
```

### 在Qml中实例化自定义C++类

```
import ClassVC 1.0
...
ClassVC {
    id: classVC
}
```

### 在Qml中调用C++函数

```js
function refresh() { //js函数
    classVC.refresh() //C++函数
    classListModel.clear()
    endedClassListModel.clear()
    classVC.classList.forEach(ele => {
      if (ele.status === 0) {
          classListModel.append(ele)
      } else {
          endedClassListModel.append(ele)
			}
		})
}
```

### 将C++ Vector容器的内容呈现在Qml的列表上

```c++
//classscoreviewcontroller.h 截取部分
Q_PROPERTY(QJsonArray scoreList READ getScoreList CONSTANT)
public:
		Q_INVOKABLE void getData(long classId);
    QJsonArray getScoreList();
```

```c++
//classscoreviewcontroller.cpp 截取部分
void ClassScoreViewController::getData(long classId) {
  	//清空原有列表
    while (scoreList.count()) {
        scoreList.pop_back();
    }
    try {
      	//获取数据
        std::vector<DataManager::ScoreListItem> list = DataManager::getScoreList(classId);
        if (list.size() == 0)
            return;
        double min = (std::numeric_limits<double>::max)(), max = 0, sum = 0;
      	//遍历vector
        for (auto item : list) {
            if (item.score > max) {
                max = item.score;
            }
            if (item.score < min) {
                min = item.score;
            }
            sum += item.score;
          	//新建JSON对象
            QJsonObject obj;
            obj.insert("stuId", QString::fromStdString(std::to_string(item.stuId)));
            obj.insert("name", QString::fromStdString(item.name));
            obj.insert("schoolNum", QString::fromStdString(item.schoolNum));
            obj.insert("score", QString::fromStdString(DMUtils::double2FixedStr(item.score, 2)));
          	//将JSON对象添加至JSON数组
            scoreList.append(obj);
        }
        highestScore = max;
        lowestScore = min;
        avgScore = sum / list.size();
    } catch (DataManager::DMError error) {
        qDebug() << "[ERROR] [ClassScoreViewController] " << error.what() << Qt::endl;
    }
}
```

```
//scoreWithClass.qml
//数据模型
ListModel {
    id: scoreListModel
}
//加载数据
function loadData() {
    classScoreVC.getData(classId)
    scoreListModel.clear()
    highest.text = classScoreVC.highestScore.toFixed(2)
    average.text = classScoreVC.avgScore.toFixed(2)
    lowest.text = classScoreVC.lowestScore.toFixed(2)
    //遍历JSON数组
    classScoreVC.scoreList.forEach(ele => {
        scoreListModel.append(ele)
    })
}
```



## 总结

通过编写该模块，学习了Qt Quick框架的使用方法。

本模块的优点：

- 提供了简单易用的图形界面
- 占用内存小

由于时间和能力限制，本模块还有许多不足之处：
- 未实现阴影效果
- 未实现过渡动画
- 错误提示没有单独的弹窗