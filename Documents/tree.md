```
HomeworkChecker
├─ .gitattributes
├─ .gitignore
├─ DataManager  数据库管理项目  负责人：林思行
│    ├─ DMTest
│    │    └─ main.cpp
│    ├─ DataManager
│    │    ├─ CMakeLists.txt
│    │    ├─ DBManager.cpp
│    │    ├─ DBManager.hpp
│    │    ├─ DMError.cpp
│    │    ├─ DMError.hpp
│    │    ├─ DMUtils.cpp
│    │    ├─ DMUtils.hpp
│    │    ├─ DataManager.cpp
│    │    └─ DataManager.hpp
│    ├─ DataManager.vcxproj
│    ├─ DataManager.vcxproj.filters
│    ├─ DataManager.vcxproj.user
│    └─ DataManager.xcodeproj
│           ├─ project.pbxproj
│           ├─ project.xcworkspace
│           └─ xcuserdata
├─ Documents  文档文件  负责人：林思行 杨锦荣 伍思烨
│    └─ tree.md  树状图
├─ HomeworkChecker.sln  Visual Studio解决方案
├─ HomeworkChecker.xcworkspace
│    ├─ contents.xcworkspacedata
│    ├─ xcshareddata
│    │    ├─ IDEWorkspaceChecks.plist
│    │    └─ WorkspaceSettings.xcsettings
│    └─ xcuserdata
│           └─ linsixing.xcuserdatad
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
│           ├─ .qmake.stash
│           ├─ ClassPage.qml
│           ├─ DateRectangle.qml
│           ├─ GeneralPage.qml
│           ├─ HomeworkCheckerGUI.pro
│           ├─ HomeworkCheckerGUI.pro.user
│           ├─ HomeworkCheckerGUI.vcxproj
│           ├─ HomeworkCheckerGUI.vcxproj.filters
│           ├─ HomeworkCheckerGUI.vcxproj.user
│           ├─ HomeworkCheckerGUI.xcodeproj
│           ├─ Info.plist
│           ├─ InfoOfClass.qml
│           ├─ InfoOfTask.qml
│           ├─ LaunchScreen.qml
│           ├─ LoginPage.qml
│           ├─ MarkPage.qml
│           ├─ NewAClass.qml
│           ├─ NewAssignment.qml
│           ├─ RegPage.qml
│           ├─ SettingPage.qml
│           ├─ TaskPage.qml
│           ├─ WebsocketClientForApp.cpp
│           ├─ WebsocketClientForApp.h
│           ├─ account.cpp
│           ├─ account.h
│           ├─ classscoreviewcontroller.cpp
│           ├─ classscoreviewcontroller.h
│           ├─ classviewcontroller.cpp
│           ├─ classviewcontroller.h
│           ├─ correctHomework.qml
│           ├─ correcthomework.cpp
│           ├─ correcthomework.h
│           ├─ fonts
│           ├─ generalviewcontroller.cpp
│           ├─ generalviewcontroller.h
│           ├─ icon.ico
│           ├─ icon.rc
│           ├─ images
│           ├─ infooftask.cpp
│           ├─ infooftask.h
│           ├─ main.cpp
│           ├─ main.qml
│           ├─ qml.qrc
│           ├─ scoreWithClass.qml
│           ├─ scoreWithStudent.qml
│           ├─ setting.config
│           ├─ settingpage.cpp
│           ├─ settingpage.h
│           ├─ studentscoreviewcontroller.cpp
│           ├─ studentscoreviewcontroller.h
│           ├─ taskpage.cpp
│           ├─ taskpage.h
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
│    ├─ mysql mysql使用(Win端)
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