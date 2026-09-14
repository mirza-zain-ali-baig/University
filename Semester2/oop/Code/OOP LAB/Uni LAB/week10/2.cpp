#include <iostream>
using namespace std;

class Salary{
    double *salary;

    public:
     Salary(){
         salary = nullptr;
        }
    ~Salary(){
        delete[] salary;
    }
        void input(){
        salary = new double[5];
        for(int i =0; i<5;i++){
            cout << "Enter the salary of month: " << i+1 << ": ";
            cin >> salary[i];
        }
     }
     void getSalary(){
        for(int i = 0;i<5;i++){
            cout << "SALARY OF EMPLOYEE E: " << i+1 << ": " << salary[i] << endl;
        }
     }
     double Average(){
        double average = 0, sum = 0;
        for(int i = 0;i<5;i++){
            sum = sum +salary[i];
        }
        average = sum/5;
        return average;
     }
};

class Employee{
    static int id;
    float average;
    Salary s1;
    public:
      Employee(){
        average = 0;
        id++;
      }
      Employee(const Employee &obj){
        s1 = obj.s1;
        id = ++id;
      }
      int getID(){
        return id;
      }

     void input(){
        s1.input();
        average =  s1.Average();
     }
     void getSalaryANDaverage(){
         s1.getSalary();
         cout << s1.Average() << endl;
     }
     void display(){
        s1.getSalary();
        cout << "Average: " << average << endl;
     }


     Employee operator -- (int a){
        Employee e1 = *this;
        average--;
        return e1;
     }

     Employee operator + (const Employee &e){
        Employee temp;
        temp.average = average + e.average;
        return temp;
     }
};

int Employee::id = 0;


int main(){
    Employee E1, E2, E4;

    // INputing Data
    E1.input();
    E2.input();
    E4.input();


    E1.getSalaryANDaverage();
    E2.getSalaryANDaverage();
    E1.display();
    E2.display();
    Employee E3(E4);
    E1--;

    E4 = E1 + E3;
    cout << "idvincvidcnidci\n \n \n \n ";

    E3.display();
    E1.display();
    E4.display();


    cout << "E1 ID: " << E1.getID() << endl;
    cout << "E2 ID: " << E2.getID() << endl;
    cout << "E3 ID: " << E4.getID() << endl;
    cout << "E4 ID: " << E3.getID() << endl;
}