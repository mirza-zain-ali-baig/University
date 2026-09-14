#include <iostream>
using namespace std;

struct student{
    string name;
    int roll_no;
    char section;
};

// int main(){
//     student s1;
//     s1  = {"Mirza Zain", 20, 'A'};
//     cout << s1.name << endl;
//     cout << s1.roll_no << endl;
//     cout << s1.section << endl;
// }


//2 

// int main(){
//     student s[5];
//     for(int i = 0;i<5;i++){
//         cout << "Enter std name " << i+1 << " : ";
//         cin >> s[i].name;
//         cout << "Enter std roll no. " << i+1 << " : ";
//         cin >> s[i].roll_no;
//         cout << "Enter std section " << i+1 << " : ";
//         cin >> s[i].section;
//     }
//     cout << "\n Student Data \n";
//     cout << "_______________________________________________________\n";
//     for(int i = 0; i<5;i++){
//         cout << "Student " << i+1 << ": " << s[i].name << endl;
//         cout << "Student Roll no." << i+1 << ": " << s[i].roll_no << endl;
//         cout << "Student Section " << i+1 << ": " << s[i].section << endl;
//         cout << "_______________________________________________________\n";
//     }
// }


student DetialOfStd(){
    student s1;
    s1.name = "Mirza Zain";
    s1.section = 'A';
    s1.roll_no = 20;
    return s1;
}

int main(){
    cout << DetialOfStd().name << endl;
    cout << DetialOfStd().section << endl;
    cout << DetialOfStd().roll_no << endl;
    return 0;
}