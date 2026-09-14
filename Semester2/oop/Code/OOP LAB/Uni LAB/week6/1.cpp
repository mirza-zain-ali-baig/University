#include <iostream>
using namespace std;

// class Employee{
//     const int empID;
//     string name;
//     float salary;
//     static int count;
//     public:
//      Employee(int id,string n,float s): empID(id),name(n),salary(s) { count++;};
//      void showInfo(){
//         cout << "employee ID:" << this->empID << " Name: " << this->name << " Salary: " << this->salary
//         << " Count: " << this->count << " Salary: " << this->salary << endl;
//      }

//      void totalCount(){
//         cout << "Count: " << count << endl;
//      }
// };

// int Employee::count = 0;

// int main(){
//     Employee e1(12,"Zain",122);
//     e1.totalCount();
//     Employee e2(12,"ALi",122);
//     e2.showInfo();
// }  



// Task 02
// class Student{
//     private:
//      string name;
//      int rollNo;
//      int gpa;
//     public:
//      Student(){
//         name = "Null";
//         rollNo = 0;
//         gpa = 0;
//      }
//      Student(string n,int r,int g){
//         name = n;
//         rollNo = r;
//         gpa = g;
//      }
//      void displayInfo(){
//         cout << "Name: " << name << " Roll No. : " << rollNo << " GPA: " << gpa << endl;
//      }


     
// };

// int main(){
//     Student *st = new Student("Zain",2,3);
//     st->displayInfo();
       
//     return 0;
// }


class BankAccount{
    private:
     int accountNumber;
     string holderName;
     unsigned balance;

    public:
    BankAccount(){
       accountNumber = 0;
       holderName = "Null";
       balance = 0;

    }
     BankAccount(int a, string h, int b){
        accountNumber = a;
        holderName = h;
        balance = b;
     }
     void showDetails(){
        cout << "Account Number: " << accountNumber << " Holder Name: " << holderName << " Balance: " << balance << endl;
     }

     void setHolderName(string n){
        holderName = n;
     }
     string getName() const{
        return  holderName;
     }
};

int main(){
    int size;
    cout << "Enter the size of array: ";
    cin >> size;
    BankAccount *b = new BankAccount[size];
    for(int i= 0;i<size;i++){
         b[i]=BankAccount(i,"Zain",12);
    }
    b[0].showDetails();
    b->showDetails();
    (b+1)->showDetails();
    cout << (b+1)->getName();
    delete[] b;
    return 0;

}