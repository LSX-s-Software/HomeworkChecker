# HomeworkCheckerServer

## 整体功能

服务端启动程序，主要调用QQMessage模块

## 项目结构

### 引用
- QQMessage

### 整体构成

```
HomeworkCheckerServer           服务端项目  负责人：杨锦荣
├─ CMakeLists.txt               CMake编译文件
└─ HomeworkCheckerServer.cpp    服务端程序
```

### 组件依赖
![组建依赖](pic/HomeworkCheckerServer/HomeworkCheckerServer_class.svg)

## 运行截图

### 软件运行
![服务端命令行界面](pic/HomeworkCheckerServer/1CommandWorking.png)  

### QQ端交互

#### 注册

![注册阶段截图](pic/HomeworkCheckerServer/2RegMode.png)  

#### 查询作业

![查询作业列表](pic/HomeworkCheckerServer/3GetHomework.png)  

![查询作业详情](pic/HomeworkCheckerServer/4GetHomeworkInfo.png)  

#### 提交作业

![开始提交](pic/HomeworkCheckerServer/5StartSubmit.png)  

![提交文字](pic/HomeworkCheckerServer/6WordMes.png)  

![提交图片](pic/HomeworkCheckerServer/7WordPicMes.png)  

![提交文件](pic/HomeworkCheckerServer/8FileMes.png)  

![获取已提交内容](pic/HomeworkCheckerServer/9GetText.png)  

![删除已提交内容](pic/HomeworkCheckerServer/10DeleteMes.png)  

![取消提交并保存草稿](pic/HomeworkCheckerServer/11CancelSubmit.png)  

![清空提交内容](pic/HomeworkCheckerServer/12deleteall.png)  

![提交作业](pic/HomeworkCheckerServer/13submit.png)  

#### 新消息主动提醒

![新作业提醒](pic/HomeworkCheckerServer/14NewHomeworkNotification.png)  

![作业批改提醒](pic/HomeworkCheckerServer/15HomeworkCorrectNotification.png)  