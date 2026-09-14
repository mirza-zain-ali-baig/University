#include <iostream>
using namespace std;
// Student Record Management System

struct Student {
    string name;
    int rollNo;
    int marks;
};

int main(){
    int n ;
    cout << "Enter the number of students: ";
    cin >> n;
    Student *arr = new Student[n];
    for(int i = 0;i<n;i++){
        cout << "Enter the student name fr " << i+1 << " : ";
        cin >> arr->name;
        cout << "Enter the std marsk: " << i+1 << " : ";
        cin >> arr->marks;
        cout << "Enter the std roll no for " << i+1 << " : ";
        cin >> arr->rollNo;
        arr++;
    }
    for(int i = 0;i<n;i++){
        cout << "student name for " << i+1 << " : " << arr->name << endl;
        cout << "Std marsk: " << i+1 << " : " << arr->marks << endl;
        cout << "Std roll no for " << i+1 << " : " << arr->rollNo << endl;
        arr++;
    }
    delete[] arr;
}