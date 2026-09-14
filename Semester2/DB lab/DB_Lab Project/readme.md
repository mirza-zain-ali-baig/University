# University Database Project

This repository contains a database project designed to model the core components of a university system. The project is implemented using SQL Server and includes the schema definition, sample data, a trigger, a view, and complex queries.

A detailed project report (`project of db report.docx`) is also included, which provides further documentation and an ER diagram for the database.

## Database Schema

The `university_db` database is designed to manage information about departments, programs, faculty, courses, students, and enrollments.

The schema consists of the following tables:

*   **`departments_1`**: Stores information about university departments, including department name and the head of the department (HOD).
*   **`program`**: Contains details about academic programs offered by departments.
*   **`facultey`**: Manages faculty member information, such as name, salary, and their associated department.
*   **`office`**: Assigns office rooms to faculty members.
*   **`course`**: Lists all courses, including their titles, credit hours, and the program they belong to.
*   **`sections`**: Defines specific sections for each course, linking them to a faculty member and a classroom.
*   **`student`**: Holds records of all students and their respective programs.
*   **`enrollments`**: A junction table that records student enrollments in specific course sections and their resulting grades.

Relationships are established using primary and foreign keys to ensure data integrity across the tables.

## SQL Script Features

The `SQLQuery1 project db.sql` file automates the creation and setup of the database. Its key features include:

### 1. Schema Creation and Data Insertion
The script first creates the `university_db` database and then defines the structure for all the tables listed above. Following the table creation, it populates the database with sample data to demonstrate its functionality.

### 2. Trigger
A trigger named `trg_check_credits` is implemented on the `course` table.
*   **Purpose**: To ensure data integrity by preventing the insertion of a course with zero or negative credit hours.
*   **Action**: If an `INSERT` operation attempts to add a course with `credits <= 0`, the transaction is rolled back and an error message is printed.

### 3. View
A view named `dept_summary` is created.
*   **Purpose**: To provide a simplified and quick look at essential department information.
*   **Content**: It displays the department name (`dept_name`) and the ID of the Head of Department (`hod_id`) from the `departments_1` table.

### 4. Sample Queries
The script includes examples of advanced queries to retrieve meaningful information from the database:

*   **Subquery**: A query that finds all faculty members who earn a salary greater than the average faculty salary.
*   **Complex Join**: A query that joins the `student`, `enrollments`, `sections`, and `course` tables to produce a detailed report of student enrollments, showing the student's name, the course title, the location of the class, and the grade received.

## How to Use

1.  Clone or download the repository.
2.  Open the `SQLQuery1 project db.sql` file in a SQL Server environment, such as SQL Server Management Studio (SSMS).
3.  Execute the entire script. This will:
    *   Create the `university_db` database.
    *   Define all tables and their relationships.
    *   Insert sample data into the tables.
    *   Create the `trg_check_credits` trigger and the `dept_summary` view.
    *   Run the sample `SELECT` queries.
4.  You can then interact with the database by writing your own queries against the populated tables and views.