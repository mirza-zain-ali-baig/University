#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    char* name;
    const int id;
    int marks[5];
    char grade;

public:
    Student(char a[], int i, int m[]) : id(i) {
        name = new char[strlen(a) + 1];
        strcpy(name, a);

        for (int j = 0; j < 5; j++) {
            marks[j] = m[j];
        }
    }

    ~Student() {
        delete[] name;
    }

    void GradeCalculate() {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += marks[i];
        }

        float average = sum / 5.0;

        if (average >= 90)
            grade = 'A';
        else if (average >= 80)
            grade = 'B';
        else if (average >= 70)
            grade = 'C';
        else if (average >= 60)
            grade = 'D';
        else
            grade = 'F';
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Marks: ";
        for (int i = 0; i < 5; i++) {
            cout << marks[i] << " ";
        }
        cout << "\nGrade: " << grade << endl;
    }
};

int main() {
    int totalStudents;
    cout << "Enter the number of Students: ";
    cin >> totalStudents;
    
    Student** s = new Student*[totalStudents];
    
    for (int i = 0; i < totalStudents; i++) {
        cin.ignore();
        char* name;;
        cout << "Enter name: ";
        cin.getline(name, 100);

        int id;
        cout << "Enter ID: ";
        cin >> id;

        int marks[5];
        cout << "Enter 5 marks: ";
        for (int j = 0; j < 5; j++) {
            cin >> marks[j];
        }

        s[i] = new Student(name, id, marks);
        s[i]->GradeCalculate();

        delete[] name;
    }

    cout << "\n\n== Student Records ==\n\n";
    for (int i = 0; i < totalStudents; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        s[i]->display();
    }

    for (int i = 0; i < totalStudents; i++)
        delete s[i];
    delete[] s;

    return 0;
}
