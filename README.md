# **作业管理系统产品文档**

## Homework Checker

## 开发者

[**@NagisaCo** NagisaCo](https://github.com/NagisaCo)

[**@LSX-s-Software** Sixing Lin](https://github.com/LSX-s-Software)

[**@WuSiye** Siye Wu](https://github.com/WuSiye)

## 编译、运行方法

### Windows

系统要求：

- 安装Visual Studio 2019、Qt 5

### Mac

系统要求：

- 系统版本不低于macOS 10.15（推荐11.0或以上）
- 安装Xcode 12、Qt 6.1

### 运行前准备

1. 在本地或远程服务器上安装MySQL（版本不低于8.0）

2. 在MySQL数据库中创建名为`homework_checker`的数据库

3. 连接数据库后在`homework_checker`里导入本仓库根目录下的`Setup.sql`

   ```sql
   mysql> source /some/where/Setup.sql;
   ```
   
4. 在服务器上运行服务端程序

5. 更新`DataManager/DataManager/DataManager.cpp`的`connectDatabase()`函数中的数据库登录信息和`UserInterface/HomeworkCheckerGUI/settingpage.cpp`中的`wsClientUrl`属性

## 产品介绍

| **产品定位** | 一款服务于大学教师与学生的教学辅助系统                       |
| ------------ | ------------------------------------------------------------ |
| **产品描述** | 教师可在此系统上布置作业、批改作业、记录成绩；学生可以通过发送邮件到特定QQ号提交作业；教师批改完毕后会将评语和成绩发送至学生的邮箱。期末时教师可以通过此系统一键导出平时成绩。 |
| **目标人群** | 大学教师、学生，尤其是程序设计课的教师和学生                 |
| **使用场景** | 学生提交作业、查看批改结果，教师布置作业、批改作业、记录成绩 |



## 产品功能结构

### **学生端**（使用QQ）

- 查看教师布置的作业
- 提交作业
  - 文本
  - 附件
- 查看批改结果
  - 成绩
  - 评语

### 教师端

- 查看学生提交的作业
- 作业打分、写评语
- 查看、导出平时成绩

- 使用数据库储存学生名单、作业、成绩



## 数据结构设计

### 类设计

- 学生类（Student）
  - ID
  - 学号
  - QQ号
  - 班级ID
  - 姓名
  - 注册时间
- 布置的作业类（Assignment）
  - ID
  - 教师ID
  - 标题
  - 描述
  - 创建时间
  - 截止日期
  - 目标班级
- 学生提交的作业类（Homework）
  - ID
  - 学生ID
  - 布置的作业ID
  - 内容URL
  - 附件URL
  - 成绩
  - 评语
- 班级类（Class）
  - ID
  - 教师ID
  - 名称
  - 上课地点
  - 上课时间
  - 人数
  - 邀请码
  - 状态

### 数据库表设计

- 帐号表（users）

| 字段     | id   | username    | password    | type                       | avatar_url   | name        |
| -------- | ---- | ----------- | ----------- | -------------------------- | ------------ | ----------- |
| 数据类型 | INT  | VARCHAR(50) | VARCHAR(50) | TINYINT(1)                 | VARCHAR(100) | VARCHAR(15) |
| 描述     |      | 用户名      | 密码        | 用户类型（0=教师，1=学生） | 头像URL      | 教师姓名    |

- 布置的作业表（assignments）

| 字段     | id     | teacher_id   | title       | description | start_date | deadline  | class_id   |
| -------- | ------ | ------------ | ----------- | ----------- | ---------- | --------- | ---------- |
| 数据类型 | BIGINT | INT          | VARCHAR(80) | TEXT        | TIMESTAMP  | TIMESTAMP | INT        |
| 描述     |        | 布置的教师ID | 标题        | 描述        | 布置时间   | 截止时间  | 目标班级ID |

- 提交的作业表（homework）

| 字段     | id     | student_id | assignment_id | content_url  | attachment_url | score    | comments |
| -------- | ------ | ---------- | ------------- | ------------ | -------------- | -------- | -------- |
| 数据类型 | BIGINT | INT        | BIGINT        | VARCHAR(600) | VARCHAR(600)   | SMALLINT | TEXT     |
| 描述     |        | 学生ID     |               | 作答文件URL  | 附件URL        | 成绩     | 评语     |

- 班级表（classes）

| 字段     | id     | teacher_id | name        | location    | time        | code    | status             |
| -------- | ------ | ---------- | ----------- | ----------- | ----------- | ------- | ------------------ |
| 数据类型 | BIGINT | INT        | VARCHAR(25) | VARCHAR(20) | VARCHAR(10) | CHAR(4) | TINYINT(1)         |
| 描述     |        | 教师ID     | 名称        | 上课地点    | 上课时间    | 邀请码  | 0=未结课，1=已结课 |

- 学生表（students）

| 字段     | id   | school_num | qq          | class_id | name        | register_time |
| -------- | ---- | ---------- | ----------- | -------- | ----------- | ------------- |
| 数据类型 | INT  | CHAR(11)   | VARCHAR(15) | INT      | VARCHAR(20) | TIMESTAMP     |
| 描述     |      | 学号       | QQ号        | 班级ID   | 姓名        | 注册时间      |



## 产品界面UI设计

Adobe XD设计图

```
./src/ui/教师端.xd
```

