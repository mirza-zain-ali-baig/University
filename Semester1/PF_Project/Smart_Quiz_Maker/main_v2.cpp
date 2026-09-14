#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

// Color codes
enum Colors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

// Function to set text color
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to center text
void centerText(const string& text) {
    cout << setw(70) << text << endl;    
}

void centerChoice(const string& text){
    cout << setw(55) << text << endl; 
}

// Function to draw simple centered box
void drawSimpleBox(const string& title, const vector<string>& content) {
    cout << title << endl;
    
    for (const string& line : content) {
        cout << line << endl;
    }
}

// Function to draw a horizontal line
void drawLine(char symbol = '=', int color = BRIGHT_WHITE) {
     int width = 80;
    setColor(color);
    cout << string(width, symbol) << endl;
    setColor(WHITE);
}

// Function to clear screen
void clearScreen() {
    system("cls");
}

// Structure to store user information
struct User {
    string username;
    string password;
    string role; // "admin", "teacher", or "student"
    string designation;
    string contact;
};

// Structure to store question information
struct Question {
    string questionText;
    string options[4];
    int correctOption;
    string subject;
    int timeLimit; // Time limit in seconds for this question
};

// Structure to store quiz information
struct Quiz {
    string title;
    string description;
    Question questions[10]; // Fixed size array for simplicity
    int questionCount;
    string assignedClass;
    int totalTimeLimit; // Total time limit for the quiz in minutes
    bool isRandomized; // Whether questions and options should be randomized
};

// Structure to store result information
struct Result {
    string studentUsername;
    string quizTitle;
    int score;
    int totalQuestions;
    string grade;
    string subject;
};

// Structure to store subject grades
struct SubjectGrade {
    string studentUsername;
    string subject;
    string grade;
    int totalMarks;
    int obtainedMarks;
};

// Global variables
User users[100]; // Fixed size array for simplicity
int userCount = 0;
Quiz quizzes[50]; // Fixed size array for simplicity
int quizCount = 0;
Result results[500]; // Fixed size array for simplicity
int resultCount = 0;
SubjectGrade grades[500]; // Fixed size array for simplicity
int gradeCount = 0;
User currentUser;

// File names for data persistence
const string USERS_FILE = "users.txt";
const string QUIZZES_FILE = "quizzes.txt";
const string RESULTS_FILE = "results.txt";
const string GRADES_FILE = "grades.txt";

// Function declarations
void displayWelcomeBanner();
void mainMenu();
void registerUser();
void login();
void adminDashboard();
void teacherDashboard();
void studentDashboard();
void displayAdminHeader();
void displayTeacherHeader();
void displayStudentHeader();
void createQuiz();
void assignQuizToClass();
string calculateGrade(int score, int total);
void loadData();
void saveData();

// Function to calculate grade based on score
string calculateGrade(int score, int total) {
    float percentage = (float)score / total * 100;
    if (percentage >= 90) return "A+";
    if (percentage >= 80) return "A";
    if (percentage >= 70) return "B";
    if (percentage >= 60) return "C";
    if (percentage >= 50) return "D";
    return "F";
}

// Function to load data from files
void loadData() {
    // Load users
    ifstream userFile(USERS_FILE);
    if (userFile.is_open()) {
        userCount = 0;
        while (userFile >> users[userCount].username >> users[userCount].password 
               >> users[userCount].role >> users[userCount].designation >> users[userCount].contact) {
            userCount++;
        }
        userFile.close();
    }

    // Load quizzes
    ifstream quizFile(QUIZZES_FILE);
    if (quizFile.is_open()) {
        quizCount = 0;
        while (getline(quizFile, quizzes[quizCount].title)) {
            getline(quizFile, quizzes[quizCount].description);
            quizFile >> quizzes[quizCount].questionCount >> quizzes[quizCount].assignedClass 
                     >> quizzes[quizCount].totalTimeLimit >> quizzes[quizCount].isRandomized;
            quizFile.ignore();
            for (int i = 0; i < quizzes[quizCount].questionCount; i++) {
                getline(quizFile, quizzes[quizCount].questions[i].questionText);
                for (int j = 0; j < 4; j++) {
                    getline(quizFile, quizzes[quizCount].questions[i].options[j]);
                }
                quizFile >> quizzes[quizCount].questions[i].correctOption 
                        >> quizzes[quizCount].questions[i].subject 
                        >> quizzes[quizCount].questions[i].timeLimit;
                quizFile.ignore();
            }
            quizCount++;
        }
        quizFile.close();
    }

    // Load results
    ifstream resultFile(RESULTS_FILE);
    if (resultFile.is_open()) {
        resultCount = 0;
        while (resultFile >> results[resultCount].studentUsername >> results[resultCount].quizTitle 
               >> results[resultCount].score >> results[resultCount].totalQuestions 
               >> results[resultCount].grade >> results[resultCount].subject) {
            resultCount++;
        }
        resultFile.close();
    }

    // Load grades
    ifstream gradeFile(GRADES_FILE);
    if (gradeFile.is_open()) {
        gradeCount = 0;
        while (gradeFile >> grades[gradeCount].studentUsername >> grades[gradeCount].subject 
               >> grades[gradeCount].grade >> grades[gradeCount].totalMarks 
               >> grades[gradeCount].obtainedMarks) {
            gradeCount++;
        }
        gradeFile.close();
    }
}

// Function to save data to files
void saveData() {
    // Save users
    ofstream userFile(USERS_FILE);
    for (int i = 0; i < userCount; i++) {
        userFile << users[i].username << " " << users[i].password << " " << users[i].role 
                 << " " << users[i].designation << " " << users[i].contact << endl;
    }
    userFile.close();

    // Save quizzes
    ofstream quizFile(QUIZZES_FILE);
    for (int i = 0; i < quizCount; i++) {
        quizFile << quizzes[i].title << endl;
        quizFile << quizzes[i].description << endl;
        quizFile << quizzes[i].questionCount << " " << quizzes[i].assignedClass 
                 << " " << quizzes[i].totalTimeLimit << " " << quizzes[i].isRandomized << endl;
        for (int j = 0; j < quizzes[i].questionCount; j++) {
            quizFile << quizzes[i].questions[j].questionText << endl;
            for (int k = 0; k < 4; k++) {
                quizFile << quizzes[i].questions[j].options[k] << endl;
            }
            quizFile << quizzes[i].questions[j].correctOption << " " 
                     << quizzes[i].questions[j].subject << " " 
                     << quizzes[i].questions[j].timeLimit << endl;
        }
    }
    quizFile.close();

    // Save results
    ofstream resultFile(RESULTS_FILE);
    for (int i = 0; i < resultCount; i++) {
        resultFile << results[i].studentUsername << " " << results[i].quizTitle 
                  << " " << results[i].score << " " << results[i].totalQuestions 
                  << " " << results[i].grade << " " << results[i].subject << endl;
    }
    resultFile.close();

    // Save grades
    ofstream gradeFile(GRADES_FILE);
    for (int i = 0; i < gradeCount; i++) {
        gradeFile << grades[i].studentUsername << " " << grades[i].subject 
                  << " " << grades[i].grade << " " << grades[i].totalMarks 
                  << " " << grades[i].obtainedMarks << endl;
    }
    gradeFile.close();
}

// Function to display welcome banner
void displayWelcomeBanner() {
    clearScreen();
    cout << "\n\n";
    setColor(BRIGHT_CYAN);
    centerText("==========================================");
    centerText("            SMART QUIZ MAKER             ");
    centerText("==========================================");
    centerText("            Welcome to the System         ");
    centerText("==========================================");
    setColor(WHITE);
    cout << "\n";
}

// Function to display main menu
void mainMenu() {
    clearScreen();
    displayWelcomeBanner();
    setColor(BRIGHT_GREEN);
    centerText("==========================================");
    centerText("                MAIN MENU                 ");
    centerText("==========================================");
    centerText("              1. Register                 ");
    centerText("              2. Login                    ");
    centerText("              3. Exit                     ");
    centerText("==========================================");
    setColor(BRIGHT_YELLOW);
    centerChoice("Enter your choice: ");
    setColor(WHITE);
}

// Function to handle registration
void registerUser() {
    clearScreen();
    displayWelcomeBanner();
    cout << "\n===== User Registration =====\n";
    
    if (userCount < 100) {
        User newUser;
        
        cout << "Enter username (min 4 characters): ";
        getline(cin, newUser.username);
        
        // Validate username
        if (newUser.username.length() < 4) {
            cout << "Username must be at least 4 characters long!\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }
        
        // Check if username already exists
        for (int i = 0; i < userCount; i++) {
            if (users[i].username == newUser.username) {
                cout << "Username already exists! Please choose another one.\n";
                cout << "Press Enter to continue...";
                cin.get();
                return;
            }
        }
        
        cout << "Enter password (min 8 characters): ";
        getline(cin, newUser.password);
        
        // Validate password
        if (newUser.password.length() < 8) {
            cout << "Password must be at least 8 characters long!\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }
        
        cout << "Enter role (admin/teacher/student): ";
        getline(cin, newUser.role);
        
        // Validate role
        if (newUser.role != "admin" && newUser.role != "teacher" && newUser.role != "student") {
            cout << "Invalid role! Please choose from admin, teacher, or student.\n";
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }
        
        cout << "Enter designation: ";
        getline(cin, newUser.designation);
        
        cout << "Enter contact: ";
        getline(cin, newUser.contact);
        
        users[userCount] = newUser;
        userCount++;
        saveData();
        
        cout << "\nRegistration successful!\n";
        cout << "Please login with your credentials.\n";
        cout << "Press Enter to continue...";
        cin.get();
    } else {
        cout << "Maximum user limit reached!\n";
        cout << "Press Enter to continue...";
        cin.get();
    }
}

// Function to display admin dashboard header
void displayAdminHeader() {
    clearScreen();
    cout << "\n";
    setColor(BRIGHT_MAGENTA);
    centerText("==========================================");
    centerText("             ADMIN DASHBOARD              ");
    centerText("==========================================");
    centerChoice("Welcome, " + currentUser.username);
    centerChoice(currentUser.designation);
    centerText("==========================================");
    setColor(WHITE);
    cout << "\n";
}

// Function to display teacher dashboard header
void displayTeacherHeader() {
    clearScreen();
    cout << "\n";
    setColor(BRIGHT_GREEN);
    centerText("==========================================");
    centerText("            TEACHER DASHBOARD             ");
    centerText("==========================================");
    centerChoice("Welcome, " + currentUser.username);
    centerChoice(currentUser.designation);
    centerText("==========================================");
    setColor(WHITE);
    cout << "\n";
}

// Function to display student dashboard header
void displayStudentHeader() {
    clearScreen();
    cout << "\n";
    setColor(BRIGHT_BLUE);
    centerText("==========================================");
    centerText("            STUDENT DASHBOARD             ");
    centerText("==========================================");
    centerChoice("Welcome, " + currentUser.username);
    centerText("==========================================");
    setColor(WHITE);
    cout << "\n";
}

// Function to display quiz box
void displayQuizBox(const string& title, const string& content) {
    setColor(BRIGHT_YELLOW);
    centerText("╔══════════════════════════════════════════╗");
    centerText("║ " + string(38 - title.length(), ' ') + title + " ║");
    centerText("╠══════════════════════════════════════════╣");
    setColor(BRIGHT_WHITE);
    
    stringstream ss(content);
    string line;
    while (getline(ss, line)) {
        centerText("║ " + string(38 - line.length(), ' ') + line + " ║");
    }
    
    setColor(BRIGHT_YELLOW);
    centerText("╚══════════════════════════════════════════╝");
    setColor(WHITE);
}

// Function to display success message
void displaySuccess(const string& message) {
    setColor(BRIGHT_GREEN);
    centerText("==========================================");
    centerText("✓ " + message);
    centerText("==========================================");
    setColor(WHITE);
}

// Function to display error message
void displayError(const string& message) {
    setColor(BRIGHT_RED);
    centerText("==========================================");
    centerText("✗ " + message);
    centerText("==========================================");
    setColor(WHITE);
}

// Function to display warning message
void displayWarning(const string& message) {
    setColor(BRIGHT_YELLOW);
    centerText("==========================================");
    centerText("! " + message);
    centerText("==========================================");
    setColor(WHITE);
}

// Function to handle quiz assignment
void assignQuizToClass() {
    clearScreen();
    cout << "\n===== Assign Quiz to Class =====\n";
    
    // Display available quizzes
    cout << "Available quizzes:\n";
    int availableCount = 0;
    int availableIndices[50];
    
    for (int i = 0; i < quizCount; i++) {
        if (quizzes[i].assignedClass == "unassigned") {
            cout << availableCount + 1 << ". " << quizzes[i].title << "\n";
            cout << "   Description: " << quizzes[i].description << "\n";
            cout << "   Questions: " << quizzes[i].questionCount << "\n";
            cout << "   Subject: " << quizzes[i].questions[0].subject << "\n";
            cout << "------------------------\n";
            availableIndices[availableCount] = i;
            availableCount++;
        }
    }
    
    if (availableCount == 0) {
        cout << "No unassigned quizzes available.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }
    
    cout << "Select quiz to assign (1-" << availableCount << "): ";
    int quizChoice;
    cin >> quizChoice;
    cin.ignore();
    
    if (quizChoice > 0 && quizChoice <= availableCount) {
        int quizIndex = availableIndices[quizChoice - 1];
        
        cout << "Enter class name: ";
        string className;
        getline(cin, className);
        
        quizzes[quizIndex].assignedClass = className;
        saveData();
        
        cout << "\nQuiz assigned successfully to class: " << className << "\n";
    } else {
        cout << "Invalid quiz selection!\n";
    }
    
    cout << "Press Enter to continue...";
    cin.get();
}

// Function to handle quiz creation
void createQuiz() {
    clearScreen();
    setColor(BRIGHT_CYAN);
    centerText("===== Create New Quiz =====");
    setColor(WHITE);
    
    if (quizCount < 50) {
        Quiz newQuiz;
        
        setColor(BRIGHT_WHITE);
        centerText("Enter quiz title: ");
        getline(cin, newQuiz.title);
        
        centerText("Enter quiz description: ");
        getline(cin, newQuiz.description);
        
        centerText("How many questions? (max 10): ");
        cin >> newQuiz.questionCount;
        cin.ignore();
        
        if (newQuiz.questionCount > 10) {
            displayError("Maximum 10 questions allowed!");
            cout << "Press Enter to continue...";
            cin.get();
            return;
        }
        
        centerText("Enter total time limit (in minutes): ");
        cin >> newQuiz.totalTimeLimit;
        cin.ignore();
        
        centerText("Randomize questions? (1 for yes, 0 for no): ");
        cin >> newQuiz.isRandomized;
        cin.ignore();
        
        for (int i = 0; i < newQuiz.questionCount; i++) {
            clearScreen();
            setColor(BRIGHT_CYAN);
            centerText("===== Question " + to_string(i + 1) + " =====");
            setColor(WHITE);
            
            centerText("Enter question text: ");
            getline(cin, newQuiz.questions[i].questionText);
            
            for (int j = 0; j < 4; j++) {
                centerText("Enter option " + to_string(j + 1) + ": ");
                getline(cin, newQuiz.questions[i].options[j]);
            }
            
            centerText("Enter correct option (1-4): ");
            cin >> newQuiz.questions[i].correctOption;
            cin.ignore();
            
            centerText("Enter subject: ");
            getline(cin, newQuiz.questions[i].subject);
            
            centerText("Enter time limit for this question (in seconds): ");
            cin >> newQuiz.questions[i].timeLimit;
            cin.ignore();
        }
        
        newQuiz.assignedClass = "unassigned";
        quizzes[quizCount] = newQuiz;
        quizCount++;
        saveData();
        
        displaySuccess("Quiz created successfully!");
    } else {
        displayError("Maximum quiz limit reached!");
    }
    
    cout << "Press Enter to continue...";
    cin.get();
}

// Function for admin dashboard
void adminDashboard() {
    while (true) {
        displayAdminHeader();
        cout << "\n===== Menu Options =====\n";
        cout << "1. Register User(Admin, Teacher, Student)\n";
        cout << "2. View All Users\n";
        cout << "3. Search User\n";
        cout << "4. Remove User\n";
        cout << "5. Update User Information\n";
        cout << "6. Generate User Credentials\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // Register new user
            clearScreen();
            cout << "\n===== Register New User =====\n";
            if (userCount < 100) {
                cout << "Enter username: ";
                getline(cin, users[userCount].username);
                cout << "Enter password: ";
                getline(cin, users[userCount].password);
                cout << "Enter role (admin/teacher/student): ";
                getline(cin, users[userCount].role);
                cout << "Enter designation: ";
                getline(cin, users[userCount].designation);
                cout << "Enter contact: ";
                getline(cin, users[userCount].contact);
                userCount++;
                saveData();
                cout << "\nUser registered successfully!\n";
            } else {
                cout << "Maximum user limit reached!\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 2) {
            // View all users
            clearScreen();
            cout << "\n===== All Users =====\n";
            for (int i = 0; i < userCount; i++) {
                cout << "Username: " << users[i].username << "\n";
                cout << "Role: " << users[i].role << "\n";
                cout << "Designation: " << users[i].designation << "\n";
                cout << "Contact: " << users[i].contact << "\n";
                cout << "------------------------\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 3) {
            // Search user
            clearScreen();
            cout << "\n===== Search User =====\n";
            string searchUsername;
            cout << "Enter username to search: ";
            getline(cin, searchUsername);
            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == searchUsername) {
                    cout << "\nUser found:\n";
                    cout << "Username: " << users[i].username << "\n";
                    cout << "Role: " << users[i].role << "\n";
                    cout << "Designation: " << users[i].designation << "\n";
                    cout << "Contact: " << users[i].contact << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "User not found!\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 4) {
            // Remove user
            clearScreen();
            cout << "\n===== Remove User =====\n";
            string removeUsername;
            cout << "Enter username to remove: ";
            getline(cin, removeUsername);
            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == removeUsername) {
                    // Shift remaining users
                    for (int j = i; j < userCount - 1; j++) {
                        users[j] = users[j + 1];
                    }
                    userCount--;
                    saveData();
                    cout << "\nUser removed successfully!\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "User not found!\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 5) {
            // Update user information
            clearScreen();
            cout << "\n===== Update User Information =====\n";
            string updateUsername;
            cout << "Enter username to update: ";
            getline(cin, updateUsername);
            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == updateUsername) {
                    cout << "Enter new password: ";
                    getline(cin, users[i].password);
                    cout << "Enter new designation: ";
                    getline(cin, users[i].designation);
                    cout << "Enter new contact: ";
                    getline(cin, users[i].contact);
                    saveData();
                    cout << "\nUser information updated successfully!\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "User not found!\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 6) {
            // Generate user credentials
            clearScreen();
            cout << "\n===== Generate User Credentials =====\n";
            string username;
            cout << "Enter username: ";
            getline(cin, username);
            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == username) {
                    cout << "\nUser Credentials:\n";
                    cout << "Username: " << users[i].username << "\n";
                    cout << "Password: " << users[i].password << "\n";
                    cout << "Role: " << users[i].role << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "User not found!\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}

// Function for teacher dashboard
void teacherDashboard() {
    while (true) {
        displayTeacherHeader();
        cout << "\n===== Menu Options =====\n";
        cout << "1. Create Quiz\n";
        cout << "2. View My Quizzes\n";
        cout << "3. Edit Quiz\n";
        cout << "4. Assign Quiz to Class\n";
        cout << "5. View Class Results\n";
        cout << "6. View Student Results\n";
        cout << "7. Assign Grades\n";
        cout << "8. Update Information\n";
        cout << "9. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            createQuiz();
        } else if (choice == 2) {
            // View my quizzes
            clearScreen();
            cout << "\n===== My Quizzes =====\n";
            for (int i = 0; i < quizCount; i++) {
                cout << i+1 << ". " << quizzes[i].title << "\n";
                cout << "Description: " << quizzes[i].description << "\n";
                cout << "Questions: " << quizzes[i].questionCount << "\n";
                cout << "Time Limit: " << quizzes[i].totalTimeLimit << " minutes\n";
                cout << "Class: " << quizzes[i].assignedClass << "\n";
                cout << "------------------------\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 3) {
            // Edit quiz implementation
            clearScreen();
            cout << "\n===== Edit Quiz =====\n";
            // ... (Add quiz editing implementation)
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 4) {
            assignQuizToClass();
        } else if (choice == 5) {
            // View class results
            clearScreen();
            cout << "\n===== Class Results =====\n";
            string className;
            cout << "Enter class name: ";
            getline(cin, className);
            
            bool found = false;
            for (int i = 0; i < resultCount; i++) {
                for (int j = 0; j < quizCount; j++) {
                    if (quizzes[j].assignedClass == className && 
                        results[i].quizTitle == quizzes[j].title) {
                        cout << "Student: " << results[i].studentUsername << "\n";
                        cout << "Quiz: " << results[i].quizTitle << "\n";
                        cout << "Score: " << results[i].score << "/" << results[i].totalQuestions << "\n";
                        cout << "Grade: " << results[i].grade << "\n";
                        cout << "------------------------\n";
                        found = true;
                    }
                }
            }
            if (!found) {
                cout << "No results found for this class.\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 6) {
            // View student results
            clearScreen();
            cout << "\n===== Student Results =====\n";
            string studentUsername;
            cout << "Enter student username: ";
            getline(cin, studentUsername);
            
            bool found = false;
            for (int i = 0; i < resultCount; i++) {
                if (results[i].studentUsername == studentUsername) {
                    cout << "Quiz: " << results[i].quizTitle << "\n";
                    cout << "Score: " << results[i].score << "/" << results[i].totalQuestions << "\n";
                    cout << "Grade: " << results[i].grade << "\n";
                    cout << "Subject: " << results[i].subject << "\n";
                    cout << "------------------------\n";
                    found = true;
                }
            }
            if (!found) {
                cout << "No results found for this student.\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 7) {
            // Assign grades
            clearScreen();
            cout << "\n===== Assign Grades =====\n";
            string studentUsername;
            cout << "Enter student username: ";
            getline(cin, studentUsername);
            
            string subject;
            cout << "Enter subject: ";
            getline(cin, subject);
            
            int totalMarks = 0;
            int obtainedMarks = 0;
            
            for (int i = 0; i < resultCount; i++) {
                if (results[i].studentUsername == studentUsername && 
                    results[i].subject == subject) {
                    totalMarks += results[i].totalQuestions;
                    obtainedMarks += results[i].score;
                }
            }
            
            if (totalMarks > 0) {
                string grade = calculateGrade(obtainedMarks, totalMarks);
                
                bool found = false;
                for (int i = 0; i < gradeCount; i++) {
                    if (grades[i].studentUsername == studentUsername && 
                        grades[i].subject == subject) {
                        grades[i].grade = grade;
                        grades[i].totalMarks = totalMarks;
                        grades[i].obtainedMarks = obtainedMarks;
                        found = true;
                        break;
                    }
                }
                
                if (!found && gradeCount < 500) {
                    grades[gradeCount].studentUsername = studentUsername;
                    grades[gradeCount].subject = subject;
                    grades[gradeCount].grade = grade;
                    grades[gradeCount].totalMarks = totalMarks;
                    grades[gradeCount].obtainedMarks = obtainedMarks;
                    gradeCount++;
                }
                
                saveData();
                cout << "\nGrade assigned successfully!\n";
                cout << "Grade: " << grade << "\n";
                cout << "Marks: " << obtainedMarks << "/" << totalMarks << "\n";
            } else {
                cout << "No results found for this student in the given subject.\n";
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 8) {
            // Update information
            clearScreen();
            cout << "\n===== Update Information =====\n";
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == currentUser.username) {
                    cout << "Enter new password: ";
                    getline(cin, users[i].password);
                    cout << "Enter new designation: ";
                    getline(cin, users[i].designation);
                    cout << "Enter new contact: ";
                    getline(cin, users[i].contact);
                    currentUser = users[i];
                    saveData();
                    cout << "\nInformation updated successfully!\n";
                    break;
                }
            }
            cout << "Press Enter to continue...";
            cin.get();
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
}

// Function for student dashboard
void studentDashboard() {
    while (true) {
        displayStudentHeader();
        cout << "\n===== Menu Options =====\n";
        cout << "1. View Assigned Quizzes\n";
        cout << "2. Take Quiz\n";
        cout << "3. View My Results\n";
        cout << "4. View Subject Grades\n";
        cout << "5. Update Information\n";
        cout << "6. Logout\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            // View assigned quizzes
            cout << "\n===== Assigned Quizzes =====\n";
            bool found = false;
            for (int i = 0; i < quizCount; i++) {
                if (quizzes[i].assignedClass != "unassigned") {
                    cout << i+1 << ". " << quizzes[i].title << "\n";
                    cout << "Description: " << quizzes[i].description << "\n";
                    cout << "Questions: " << quizzes[i].questionCount << "\n";
                    cout << "Time Limit: " << quizzes[i].totalTimeLimit << " minutes\n";
                    cout << "------------------------\n";
                    found = true;
                }
            }
            if (!found) {
                cout << "No quizzes assigned.\n";
            }
        } else if (choice == 2) {
            // Take quiz
            cout << "\n===== Available Quizzes =====\n";
            int availableCount = 0;
            int availableIndices[50];
            
            for (int i = 0; i < quizCount; i++) {
                if (quizzes[i].assignedClass != "unassigned") {
                    cout << availableCount+1 << ". " << quizzes[i].title << " (Questions: " 
                         << quizzes[i].questionCount << ")\n";
                    availableIndices[availableCount] = i;
                    availableCount++;
                }
            }
            
            if (availableCount == 0) {
                cout << "No quizzes available for you.\n";
                continue;
            }
            
            cout << "Select quiz to take: ";
            int quizChoice;
            cin >> quizChoice;
            cin.ignore();
            
            if (quizChoice > 0 && quizChoice <= availableCount) {
                int quizIndex = availableIndices[quizChoice-1];
                Result newResult;
                newResult.studentUsername = currentUser.username;
                newResult.quizTitle = quizzes[quizIndex].title;
                newResult.score = 0;
                newResult.totalQuestions = quizzes[quizIndex].questionCount;
                newResult.subject = quizzes[quizIndex].questions[0].subject;
                
                cout << "\nTime limit: " << quizzes[quizIndex].totalTimeLimit << " minutes\n";
                cout << "Press Enter to start the quiz...";
                cin.get();
                
                for (int i = 0; i < quizzes[quizIndex].questionCount; i++) {
                    cout << "\nQuestion " << i+1 << ": " << quizzes[quizIndex].questions[i].questionText << endl;
                    cout << "Time limit: " << quizzes[quizIndex].questions[i].timeLimit << " seconds\n";
                    
                    for (int j = 0; j < 4; j++) {
                        cout << j+1 << ". " << quizzes[quizIndex].questions[i].options[j] << endl;
                    }
                    
                    cout << "Your answer (1-4): ";
                    int answer;
                    cin >> answer;
                    cin.ignore();
                    
                    if (answer == quizzes[quizIndex].questions[i].correctOption) {
                        newResult.score++;
                    }
                }
                
                newResult.grade = calculateGrade(newResult.score, newResult.totalQuestions);
                
                if (resultCount < 500) {
                    results[resultCount] = newResult;
                    resultCount++;
                    saveData();
                }
                
                cout << "\nQuiz completed!\n";
                cout << "Your score: " << newResult.score << "/" << newResult.totalQuestions << endl;
                cout << "Grade: " << newResult.grade << endl;
            } else {
                cout << "Invalid choice.\n";
            }
        } else if (choice == 3) {
            // View my results
            cout << "\n===== My Results =====\n";
            bool found = false;
            for (int i = 0; i < resultCount; i++) {
                if (results[i].studentUsername == currentUser.username) {
                    cout << "Quiz: " << results[i].quizTitle << "\n";
                    cout << "Score: " << results[i].score << "/" << results[i].totalQuestions << "\n";
                    cout << "Grade: " << results[i].grade << "\n";
                    cout << "Subject: " << results[i].subject << "\n";
                    cout << "------------------------\n";
                    found = true;
                }
            }
            if (!found) {
                cout << "No results found.\n";
            }
        } else if (choice == 4) {
            // View subject grades
            cout << "\n===== Subject Grades =====\n";
            bool found = false;
            for (int i = 0; i < gradeCount; i++) {
                if (grades[i].studentUsername == currentUser.username) {
                    cout << "Subject: " << grades[i].subject << "\n";
                    cout << "Grade: " << grades[i].grade << "\n";
                    cout << "Marks: " << grades[i].obtainedMarks << "/" << grades[i].totalMarks << "\n";
                    cout << "------------------------\n";
                    found = true;
                }
            }
            if (!found) {
                cout << "No grades found.\n";
            }
        } else if (choice == 5) {
            // Update information
            for (int i = 0; i < userCount; i++) {
                if (users[i].username == currentUser.username) {
                    cout << "Enter new password: ";
                    cin >> users[i].password;
                    cout << "Enter new contact: ";
                    cin >> users[i].contact;
                    currentUser = users[i];
                    saveData();
                    cout << "Information updated successfully!\n";
                    break;
                }
            }
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function to handle login
void login() {
    displayWelcomeBanner();
    cout << "\n===== Login =====\n";
    
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    bool found = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            currentUser = users[i];
            found = true;
            break;
        }
    }

    if (found) {
        cout << "\nLogin successful!\n";
        if (currentUser.role == "admin") {
            adminDashboard();
        } else if (currentUser.role == "teacher") {
            teacherDashboard();
        } else if (currentUser.role == "student") {
            studentDashboard();
        }
    } else {
        cout << "\nInvalid username or password.\n";
        cout << "Press Enter to continue...";
        cin.get();
    }
}

int main() {
    loadData();

    while (true) {
        mainMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            login();
        } else if (choice == 3) {
            saveData();
            cout << "\nThank you for using Smart Quiz Maker!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cout << "Press Enter to continue...";
            cin.get();
        }
    }
    return 0;
}