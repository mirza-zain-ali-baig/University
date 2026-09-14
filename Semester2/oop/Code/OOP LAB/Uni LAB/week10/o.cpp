#include <iostream>
using namespace std;

class Salary{
    double *salary;

public:
    Salary(){
        salary = nullptr;
    }

    // deep-copy constructor
    Salary(const Salary &other){
        if(other.salary){
            salary = new double[5];
            for(int i = 0; i < 5; ++i) salary[i] = other.salary[i];
        } else {
            salary = nullptr;
        }
    }

    // deep-copy assignment
    Salary& operator=(const Salary &other){
        if(this == &other) return *this;
        delete[] salary;
        if(other.salary){
            salary = new double[5];
            for(int i = 0; i < 5; ++i) salary[i] = other.salary[i];
        } else {
            salary = nullptr;
        }
        return *this;
    }

    ~Salary(){
        delete[] salary;
    }

    void input(){
        // avoid leak if input called multiple times
        delete[] salary;
        salary = new double[5];
        for(int i = 0; i < 5; ++i){
            cout << "Enter the salary of month " << i+1 << ": ";
            cin >> salary[i];
        }
    }

    void getSalary() const {
        if (!salary) {
            cout << "No salary data available.\n";
            return;
        }
        for(int i = 0; i < 5; ++i){
            cout << "SALARY OF MONTH " << i+1 << ": " << salary[i] << endl;
        }
    }

    double Average() const {
        if (!salary) {
            // no data => average 0 (or you could choose to throw/return NAN)
            return 0.0;
        }
        double sum = 0;
        for(int i = 0; i < 5; ++i){
            sum += salary[i];
        }
        return sum / 5.0;
    }
};

class Employee{
    static int idCounter; // generates unique ids
    int id;
    float average;
    Salary s1;

public:
    Employee(){
        average = 0;
        id = ++idCounter;
    }

    // copy constructor: copy salary & average, give new unique id
    Employee(const Employee &obj){
        average = obj.average;
        s1 = obj.s1; // uses Salary::operator=
        id = ++idCounter;
    }

    int getID() const {
        return id;
    }

    void input(){
        s1.input();
        average = static_cast<float>(s1.Average());
    }

    void getSalaryANDaverage() const {
        s1.getSalary();
        cout << "Average: " << s1.Average() << endl;
    }

    void display() const {
        s1.getSalary();
        cout << "Average: " << average << endl;
    }

    // postfix decrement: returns old value
    Employee operator--(int){
        Employee e1 = *this;
        average--;
        return e1;
    }

    Employee operator+(const Employee &e) const {
        Employee temp;
        temp.average = average + e.average;
        return temp;
    }
};

int Employee::idCounter = 0;

int main(){
    Employee E1, E2, E4;

    // Inputting Data
    E1.input();
    E2.input();
    E4.input();

    E1.getSalaryANDaverage();
    E2.getSalaryANDaverage();

    E1.display();
    E2.display();

    Employee E3(E4); // copy of E4 (gets its own unique id)
    E1--;

    E4 = E1 + E3;

    E3.display();
    E1.display();
    E4.display();

    cout << "E1 ID: " << E1.getID() << endl;
    cout << "E2 ID: " << E2.getID() << endl;
    cout << "E3 ID: " << E3.getID() << endl;
    cout << "E4 ID: " << E4.getID() << endl;

    return 0;
}
