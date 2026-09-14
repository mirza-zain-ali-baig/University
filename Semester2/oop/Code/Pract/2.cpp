#include <iostream>
#include <string>
using namespace std;

class Option {
private:
    string text;

public:
    Option() {
        text = "Null";
    }

    Option(string t) {
        text = t;
    }

    string getOption() {
        return text;
    }
};

class Question {
private:
    string questionText;
    Option options[4];
    int optionCount;
    int correctOption;

public:
    Question() {
        questionText = "Null";
        optionCount = 0;
        correctOption = 0 ;
    }

    Question(string q) {
        questionText = q;
        optionCount = 0;
        correctOption = 0;
    }

    void addOption(string optionText) {
        if (optionCount < 4) {
            options[optionCount] = Option(optionText);
            optionCount++;
        }
    }

    void setCorrectOption(int correct) {
        correctOption = correct;
    }

    void display() {
        cout << questionText << endl;
        cout << "Options: " << endl;
        for (int i = 0; i < optionCount; i++) {
            cout << i + 1 << " ) " << options[i].getOption() << endl;
        }
    }

    bool checkAnswer(int userChoice) {
        return (userChoice == correctOption);
    }
};

int main() {
    int totalQuestions = 4;
    int score = 0;
    int userAnswer;

    Question* quiz = new Question[totalQuestions];

    quiz[0] = Question("Q1: capital of Pakistan ?");
    quiz[0].addOption(" karachi ");
    quiz[0].addOption(" Islamabad");
    quiz[0].addOption(" Lahore ");
    quiz[0].addOption(" Quetta ");
    quiz[0].setCorrectOption(2);

    quiz[1] = Question("Q2: Fastest land animal?");
    quiz[1].addOption("Cheetah");
    quiz[1].addOption("Lion ");
    quiz[1].addOption("Horse ");
    quiz[1].addOption("Tiger");
    quiz[1].setCorrectOption(1);

    quiz[2] = Question("Q3: Largest ocean?");
    quiz[2].addOption("Atlantic ");
    quiz[2].addOption("Pacific");
    quiz[2].addOption("Indian");
    quiz[2].addOption("Arctic ");
    quiz[2].setCorrectOption(2);
    
    quiz[3] = Question("Q4: 2 + 2 = ?");
    quiz[3].addOption("3");
    quiz[3].addOption("5");
    quiz[3].addOption("4");
    quiz[3].addOption("22");
    quiz[3].setCorrectOption(3);
    
    for (int i = 0; i < 4; i++) {
        quiz[i].display();
        cout << "Enter your Option Number: ";
        cin >> userAnswer;

        if (quiz[i].checkAnswer(userAnswer)) {
            score++;
        }
        cout << endl;
    }

    cout << "Final Score: " << score << "/" << totalQuestions << endl;

    delete[] quiz;
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

class Course {
public:
    int courseID;
    string title;
    int teacherID;

    Course(int id, string courseName, int tId) {
        courseID = id;
        title = courseName;
        teacherID = tId;
    }
};

class Teacher {
private:
    Course* courses[3];
    int courseCount;
    int maxCourses;
    
public:
    int teacherID;
    string name;
    string role;

    Teacher(int id, string teacherName, string position) {
        teacherID = id;
        name = teacherName;
        role = position;
        courseCount = 0;

        if (role == "Principal" || role == "Lecturer") {
            maxCourses = 3;
        }
        else if (role == "Assistant Professor" || role == "Associate Professor") {
            maxCourses = 2;
        }
        else {
            maxCourses = 1;
        }
    }

    void assignCourse(Course* coursePtr) {
        if (courseCount < maxCourses) {
            courses[courseCount] = coursePtr;
            courseCount = courseCount + 1;
        }
    }

    void display() {
        cout << "  Teacher ID: " << teacherID
             << ", Name: " << name
             << ", Role: " << role << endl;

        if (courseCount == 0) {
            cout << "   No courses assigned." << endl;
        } 
        else {
            int i = 0;
            while (i < courseCount) {
                cout << "      Course ID: " << courses[i]->courseID
                     << ", Title: " << courses[i]->title << endl;
                i++;
            }
        }

        cout << "      Teacher Workload: " << courseCount << " course(s)\n\n";
    }

    int getCourseCount() {
        return courseCount;
    }
};

class Department {
private:
    Teacher* teachers[5];
    int teacherCount;

public:
    string deptName;

    Department(string departmentName) {
        deptName = departmentName;
        teacherCount = 0;
    }

    void addTeacher(Teacher* teacherPtr) {
        if (teacherCount < 5) {
            teachers[teacherCount] = teacherPtr;
            teacherCount++;
        }
    }

    void display() {
        int totalCourseCount = 0;

        cout << "Department: " << deptName << endl;
        cout << "Total Teachers: " << teacherCount << endl;

        for (int i = 0; i < teacherCount; i++) {
            int temp = teachers[i]->getCourseCount();
            totalCourseCount = totalCourseCount + temp;
        }

        cout << "Total Courses: " << totalCourseCount << "\n\n";

        for (int j = 0; j < teacherCount; j++) {
            teachers[j]->display();
        }

        cout << "=============\n";
    }
};

int main() {
    Course course1(1, "DS", 101);
    Course course2(2, "Algo", 101);
    Course course3(3, "CA", 101);
    Course course4(4, "SE", 102);
    Course course5(5, "DB", 103);
    Course course6(6, "OS", 103);
    Course course7(7, "Net", 103);
    Course course8(8, "AI", 104);
    Course course9(9, "ML", 104);

    Teacher teacher1(101, "Irfan", "Principal");
    Teacher teacher2(102, "Malik Bilal", "Professor");
    Teacher teacher3(103, "SanaRaza", "Lecturer");
    Teacher teacher4(104, "Bilal Raza", "Assistant Professor");

    teacher1.assignCourse(&course1);
    teacher1.assignCourse(&course2);
    teacher1.assignCourse(&course3);

    teacher2.assignCourse(&course4);

    teacher3.assignCourse(&course5);
    teacher3.assignCourse(&course6);
    teacher3.assignCourse(&course7);

    teacher4.assignCourse(&course8);
    teacher4.assignCourse(&course9);

    Department computerScienceDept("BSCS");
    computerScienceDept.addTeacher(&teacher1);
    computerScienceDept.addTeacher(&teacher2);
    computerScienceDept.addTeacher(&teacher3);
    computerScienceDept.addTeacher(&teacher4);

    Department itDepartment("BSIT");

    computerScienceDept.display();
    itDepartment.display();

    return 0;
}