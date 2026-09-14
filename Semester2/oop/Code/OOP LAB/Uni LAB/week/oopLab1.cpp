// Topic 1: Structures
// Task 1: Returning Structure from a Function
//  Define a structure Student with fields: id, name, and marks.
//  Write a function getTopper(Student arr[], int n) that returns the
// student structure having the highest marks.
//  In main(), input details of n students, call the function, and display
// topper’s info.

#include<iostream>
using namespace std;
struct Student{
    string id;
    string name;
    double marks;
};

Student getTopper(Student arr[], int n){
    Student highest = arr[0];
    for(int i = 0;i<n;i++){
        if(highest.marks<arr[i].marks){
            highest = arr[i];
        }
    }
    return highest;
}

int main(){
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    Student arr[n];
    for(int i = 0;i<n;i++){
        cout << "Enter the details Student " << i << endl;
        cout << "Enter the student id: ";
        cin >> arr[i].id;
        cout << "Enter the student name: ";
        cin >> arr[i].name;
        cout << "Enter the student marks: ";
        cin >> arr[i].marks;
    }

    Student highest = getTopper(arr,n);
    cout << "Topper details are: ";
    cout << highest.name << endl;
    cout << highest.id << endl;
    cout << highest.marks << endl;
    return 0;
}