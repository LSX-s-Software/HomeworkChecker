-- Database export via SQLPro (https://www.sqlprostudio.com/allapps.html)
-- Exported by linsixing at 16-05-2021 16:14.
-- WARNING: This file may contain descructive statements such as DROPs.
-- Please ensure that you are running the script at the proper location.


-- BEGIN TABLE assignments
DROP TABLE IF EXISTS assignments;
CREATE TABLE `assignments` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `teacher_id` int NOT NULL,
  `title` varchar(80) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `description` text CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `start_date` timestamp NOT NULL,
  `deadline` timestamp NOT NULL,
  `class_id` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Table assignments contains no data. No inserts have been genrated.
-- Inserting 0 rows into assignments


-- END TABLE assignments

-- BEGIN TABLE classes
DROP TABLE IF EXISTS classes;
CREATE TABLE `classes` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `teacher_id` int NOT NULL,
  `name` varchar(25) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `location` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `time` varchar(10) DEFAULT NULL,
  `code` char(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `status` tinyint unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Table classes contains no data. No inserts have been genrated.
-- Inserting 0 rows into classes


-- END TABLE classes

-- BEGIN TABLE homework
DROP TABLE IF EXISTS homework;
CREATE TABLE `homework` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `student_id` int unsigned NOT NULL,
  `content_url` varchar(60) NOT NULL,
  `attachment_url` varchar(60) DEFAULT NULL,
  `score` smallint NOT NULL DEFAULT '0',
  `comments` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Table homework contains no data. No inserts have been genrated.
-- Inserting 0 rows into homework


-- END TABLE homework

-- BEGIN TABLE students
DROP TABLE IF EXISTS students;
CREATE TABLE `students` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `school_num` char(11) NOT NULL,
  `qq` varchar(15) NOT NULL,
  `class_id` int unsigned DEFAULT NULL,
  `name` varchar(20) NOT NULL,
  `register_time` timestamp NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Table students contains no data. No inserts have been genrated.
-- Inserting 0 rows into students


-- END TABLE students

-- BEGIN TABLE users
DROP TABLE IF EXISTS users;
CREATE TABLE `users` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `password` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL DEFAULT '',
  `type` tinyint(1) NOT NULL DEFAULT '0',
  `avatar_url` varchar(100) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- END TABLE users

