# **作业管理系统产品文档**

## Homework Checker

## 开发者

[**@NagisaCo** NagisaCo](https://github.com/NagisaCo)

[**@LSX-s-Software** Sixing Lin](https://github.com/LSX-s-Software)

[**@WuSiye** Siye Wu](https://github.com/WuSiye)

## 产品介绍

| **产品定位** | 一款服务于大学教师与学生的教学辅助系统                       |
| ------------ | ------------------------------------------------------------ |
| **产品描述** | 教师可在此系统上布置作业、批改作业、记录成绩；学生可以通过发送邮件到特定邮箱提交作业；教师批改完毕后会将评语和成绩发送至学生的邮箱。期末时教师可以通过此系统一键导出平时成绩。 |
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
  - 年级、班级
  - 姓名
  - 头像URL
  - 成绩
- 布置的作业类（Assignment）
  - ID
  - 标题
  - 描述
  - 截止日期
  - 目标班级
- 学生提交的作业类（Homework）
  - ID
  - 标题
  - 内容URL
  - 附件URL
  - 成绩
  - 评语
- 班级类
  - ID
  - 名称
  - 上课地点
  - 上课时间
  - 人数
  - 邀请码

### 数据库表设计

- 帐号表（users）

| 字段     | id   | username    | password    | type                       | avatar_url   |
| -------- | ---- | ----------- | ----------- | -------------------------- | ------------ |
| 数据类型 | INT  | VARCHAR(50) | VARCHAR(50) | TINYINT(1)                 | VARCHAR(100) |
| 描述     |      | 用户名      | 密码        | 用户类型（0=教师，1=学生） | 头像URL      |

- 布置的作业表（assignments）

| 字段     | id     | teacher_id   | title       | description | start_date | deadline  | class_id   |
| -------- | ------ | ------------ | ----------- | ----------- | ---------- | --------- | ---------- |
| 数据类型 | BIGINT | INT          | VARCHAR(80) | TEXT        | TIMESTAMP  | TIMESTAMP | INT        |
| 描述     |        | 布置的教师ID | 标题        | 描述        | 布置时间   | 截止时间  | 目标班级ID |

- 提交的作业表（homework）

| 字段     | id     | student_id | content_url | attachment_url | score    | comments |
| -------- | ------ | ---------- | ----------- | -------------- | -------- | -------- |
| 数据类型 | BIGINT | INT        | VARCHAR(60) | VARCHAR(60)    | SMALLINT | TEXT     |
| 描述     |        | 学生ID     | 作答文件URL | 附件URL        | 成绩     | 评语     |

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

链接：

教师端：https://lanhuapp.com/url/O1nmX
