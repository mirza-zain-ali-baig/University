CREATE DATABASE university_db;
GO
USE university_db;
GO

-- 1. Create Tables
CREATE TABLE departments_1 (
    dept_id INT PRIMARY KEY,
    dept_name VARCHAR(50) NOT NULL,
    hod_id INT
);

CREATE TABLE program (
    prog_id INT PRIMARY KEY,
    prog_name VARCHAR(50),
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments_1(dept_id)
);

CREATE TABLE facultey (
    faculty_id INT PRIMARY KEY,
    name VARCHAR(100),
    salary DECIMAL(10,2),
    dept_id INT,
    FOREIGN KEY (dept_id) REFERENCES departments_1(dept_id)
);

CREATE TABLE office (
    office_id INT PRIMARY KEY,
    room_no VARCHAR(10),
    faculty_id INT UNIQUE,
    FOREIGN KEY (faculty_id) REFERENCES facultey(faculty_id)
);

CREATE TABLE course (
    course_id INT PRIMARY KEY,
    title VARCHAR(100),
    credits INT,
    prog_id INT,
    FOREIGN KEY (prog_id) REFERENCES program(prog_id)
);

CREATE TABLE sections (
    sect_id INT PRIMARY KEY,
    course_id INT,
    faculty_id INT,
    room VARCHAR(20),
    FOREIGN KEY (course_id) REFERENCES course(course_id),
    FOREIGN KEY (faculty_id) REFERENCES facultey(faculty_id)
);

CREATE TABLE student (
    student_id INT PRIMARY KEY,
    name VARCHAR(100),
    prog_id INT,
    FOREIGN KEY (prog_id) REFERENCES program(prog_id)
);

CREATE TABLE enrollments (
    student_id INT,
    sect_id INT,
    grade CHAR(2),
    PRIMARY KEY (student_id, sect_id),
    FOREIGN KEY (student_id) REFERENCES student(student_id),
    FOREIGN KEY (sect_id) REFERENCES sections(sect_id)
);
GO

-- 2. Insert Data
INSERT INTO departments_1 VALUES (1, 'Computer Science', 101), (2, 'Mathematics', 102);
INSERT INTO program VALUES (10, 'BS Computer Science', 1), (11, 'MS Data Science', 1);
INSERT INTO facultey VALUES (101, 'Dr. Shahzad', 95000, 1), (102, 'Dr. Ahmad', 92000, 2);
INSERT INTO office VALUES (1, 'Room 401', 101), (2, 'Room 402', 102);
INSERT INTO course VALUES (201, 'Database Systems', 3, 10), (202, 'Calculus II', 4, 10);
INSERT INTO sections VALUES (501, 201, 101, 'Lab 1'), (502, 202, 102, 'Room 10');
INSERT INTO student VALUES (301, 'Arslan Mohsin', 10), (302, 'Noman Amdad', 10);
INSERT INTO enrollments VALUES (301, 501, 'A'), (302, 501, 'B');

select * from departments_1
select * from program
select * from facultey
select * from office
select * from course
select * from sections 
select * from student
select * from enrollments
Go
-- 3. Trigger (SQL Server Syntax)
CREATE TRIGGER trg_check_credits ON course AFTER INSERT AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted WHERE credits <= 0)
    BEGIN
        PRINT 'Error: Credits must be positive';
        ROLLBACK TRANSACTION;
    END
END;
GO

-- 4. View
CREATE VIEW dept_summary AS 
SELECT dept_name, hod_id FROM departments_1;
GO
SELECT * FROM dept_summary;



-- 5. Queries for Output
-- Subquery: Faculty earning more than average
SELECT name, salary FROM facultey 
WHERE salary > (SELECT AVG(salary) FROM facultey);

-- Complex Join: Enrollment Details
SELECT 
    s.name AS [Student Name], 
    c.title AS [Course], 
    sec.room AS [Location], 
    e.grade AS [Grade]
FROM student s
JOIN enrollments e ON s.student_id = e.student_id
JOIN sections sec ON e.sect_id = sec.sect_id
JOIN course c ON sec.course_id = c.course_id;