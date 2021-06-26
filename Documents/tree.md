```
HomeworkChecker
├─ .gitattributes
├─ .gitignore
├─ DataManager  数据管理项目  负责人：林思行
│    ├─ DMTest  DataManager测试
│    │    └─ main.cpp
│    ├─ DataManager
│    │    ├─ CMakeLists.txt
│    │    ├─ DBManager.cpp
│    │    ├─ DBManager.hpp  数据库操作函数
│    │    ├─ DMError.cpp
│    │    ├─ DMError.hpp  DataManager操作异常类
│    │    ├─ DMUtils.cpp
│    │    ├─ DMUtils.hpp  DataManager实用工具
│    │    ├─ DataManager.cpp
│    │    └─ DataManager.hpp  DataManager数据管理类库（包含User、Class、Student、Homework、Assignment类）
│    ├─ DataManager.vcxproj
│    ├─ DataManager.vcxproj.filters
│    ├─ DataManager.vcxproj.user
│    └─ DataManager.xcodeproj  Xcode项目
├─ Documents  文档文件  负责人：林思行 杨锦荣 伍思烨
│    ├─ DataManager.md
│    ├─ General.md
│    ├─ GUI.md
│    ├─ HomeworkChecker.txt
│    ├─ HomeworkCheckerServer.md
│    ├─ QQMessage.md
│    ├─ tree.md  树状图（此文件）
│    │
│    ├─Analysis  项目trace  负责人：林思行
│    │  └─MemoryTrace.trace  内存泄漏检查结果
│    │
│    └─pic 文档图片
│        ├─DataManager
│        ├─General
│        ├─HomeworkCheckerServer
│        └─QQMessage
├─ HomeworkChecker.sln  Visual Studio解决方案
├─ HomeworkChecker.xcworkspace  Xcode工作区
├─ HomeworkCheckerServer  服务端项目  负责人：杨锦荣
│    ├─ CMakeLists.txt
│    ├─ HomeworkCheckerServer.cpp  服务端程序
│    ├─ HomeworkCheckerServer.vcxproj
│    ├─ HomeworkCheckerServer.vcxproj.filters
│    └─ HomeworkCheckerServer.vcxproj.user
├─ LICENSE  GPL-2.0许可
├─ QQMessage  QQ消息处理程序  负责人：杨锦荣
│    ├─ Analyst.cpp  
│    ├─ Analyst.h  文本处理及分析
│    ├─ CMakeLists.txt  
│    ├─ Exception.cpp  
│    ├─ Exception.h  自定义异常类
│    ├─ File.cpp  
│    ├─ File.h  本地文件管理类
│    ├─ FileInfo.cpp  
│    ├─ FileInfo.h  文件信息类
│    ├─ PrivateMessageGetter.h  接收私聊消息类
│    ├─ PrivateMessageSender.cpp  
│    ├─ PrivateMessageSender.h  发送私聊消息类
│    ├─ QQMessage.cpp  
│    ├─ QQMessage.h  QQ消息处理主程序
│    ├─ QQMessage.vcxproj  项目文件
│    ├─ QQMessage.vcxproj.filters  
│    ├─ QQMessage.vcxproj.user  
│    ├─ Tools.cpp  
│    ├─ Tools.h  工具类
│    ├─ WebsocketClient.cpp  
│    ├─ WebsocketClient.h  WebSocket客户端
│    ├─ WebsocketServer.cpp  
│    ├─ WebsocketServer.h  WebSocket服务端
├─ README.md  项目简介  负责人：林思行
├─ Setup.sql  Mysql配置文件  负责人：林思行 
├─ UserInterface  学生端图形化界面程序  负责人：林思行 杨锦荣 伍思烨
│    └─ HomeworkCheckerGUI
│           ├─ ClassPage.qml  “班级”页面
│           ├─ DateRectangle.qml  日期选择器
│           ├─ GeneralPage.qml  “总览”页面
│           ├─ HomeworkCheckerGUI.pro  Qt项目配置文件
│           ├─ HomeworkCheckerGUI.pro.user
│           ├─ HomeworkCheckerGUI.vcxproj
│           ├─ HomeworkCheckerGUI.vcxproj.filters
│           ├─ HomeworkCheckerGUI.vcxproj.user
│           ├─ HomeworkCheckerGUI.xcodeproj
│           ├─ Info.plist
│           ├─ InfoOfClass.qml  班级信息
│           ├─ InfoOfTask.qml  作业信息
│           ├─ LaunchScreen.qml  启动页
│           ├─ LoginPage.qml  登录页
│           ├─ MarkPage.qml  “成绩”页面
│           ├─ NewAClass.qml  新建班级
│           ├─ NewAssignment.qml  新建作业
│           ├─ RegPage.qml  注册页
│           ├─ SettingPage.qml  “设置”页面
│           ├─ TaskPage.qml  “作业”页面
│           ├─ WebsocketClientForApp.cpp
│           ├─ WebsocketClientForApp.h
│           ├─ account.cpp
│           ├─ account.h  全局帐号管理
│           ├─ classscoreviewcontroller.cpp
│           ├─ classscoreviewcontroller.h  班级分数页面控制器
│           ├─ classviewcontroller.cpp
│           ├─ classviewcontroller.h  ”班级“页面控制器
│           ├─ correctHomework.qml  批改作业
│           ├─ correcthomework.cpp
│           ├─ correcthomework.h  批改页面控制器
│           ├─ fonts  字体
│           ├─ generalviewcontroller.cpp
│           ├─ generalviewcontroller.h  ”总览“页面控制器
│           ├─ icon.ico  Windows应用图标
│           ├─ icon.rc
│           ├─ images  图片
│           ├─ infooftask.cpp
│           ├─ infooftask.h  作业详情页面控制器
│           ├─ main.cpp  启动函数
│           ├─ main.qml  主窗口
│           ├─ qml.qrc  qml资源配置文件
│           ├─ scoreWithClass.qml  班级成绩
│           ├─ scoreWithStudent.qml  学生成绩
│           ├─ setting.config
│           ├─ settingpage.cpp
│           ├─ settingpage.h  ”设置“页面控制器
│           ├─ studentscoreviewcontroller.cpp
│           ├─ studentscoreviewcontroller.h  学生成绩页面控制器
│           ├─ taskpage.cpp
│           ├─ taskpage.h  ”作业“页面控制器
│           ├─ untitled.vcxproj
│           └─ untitled.vcxproj.filters
├─ WebsocketClientForApp  学生端WebSocket库  负责人：杨锦荣
│    ├─ WebsocketClientForApp.cpp
│    ├─ WebsocketClientForApp.h  学生端WebSocket类
│    ├─ WebsocketClientForApp.vcxproj
│    ├─ WebsocketClientForApp.vcxproj.filters
│    ├─ WebsocketClientForApp.vcxproj.user
│    └─ main.cpp  测试用主函数
├─ go-cqhttp  QQ机器人(Win端)  https://github.com/Mrs4s/go-cqhttp  AGPL-3.0许可
│    ├─ config.hjson  QQ登录配置文件json
│    ├─ config.yml  QQ登录配置文件xml
│    ├─ go-cqhttp.exe  QQ机器人程序
│    ├─ start.cmd  快速启动命令
│    └─ start.lnk  快速启动快捷方式
├─ lib  临时生成静态链接库
├─ packages  引用第三方库文件
│    ├─ asio  Asio网络库 (Header Only Library)
│    ├─ json  json库 (Header Only Library)
│    ├─ mysql mysql使用(Win、Mac端)
│    └─ websocketpp websocket库(Header Only Library)
└─ src  资源文件
       ├─ icon  图标
       │    ├─ email.png
       │    ├─ homework.png
       │    ├─ name.png
       │    ├─ password.png
       │    ├─ progress.png
       │    └─ server.png
       ├─ ui  UI设计图
       │    ├─ 学生端.xd
       │    └─ 教师端.xd
       └─ 作业管理系统产品需求文档.docx  需求分析文档
```