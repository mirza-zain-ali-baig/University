#include<iostream>
using namespace std;

class Department{
    string deptName;
    string faculty[50];
    string Students[300];
    string courses[10];
    int fcount;
    int scount;
    int cCount;
    public:
        Department(){
            fcount = 0;
            scount = 0;
            cCount = 0;
        }
     void setDeptName(string name){
        deptName = name;
     }

     void setFaculty(string *t, int n){
        for(int i = 0; i < n && fcount < 50; i++){
            faculty[fcount++] = t[i];
        }
     }
     void setStudent(string *s, int n){
        for(int i = 0; i < n && scount < 300; i++){
            Students[scount++] = s[i];
        }
     }
     void setCourses(string *c, int n){
        for(int i = 0; i < n && cCount < 10; i++){
            courses[cCount++] = c[i];
        }
     }

     void displayy(){
        for(int i= 1;i<fcount;i++){
            cout << "Faculty: " << faculty[i] << endl;
        }
        for(int i= 1;i<scount;i++){
            cout << "Students: " << Students[i] << endl;
        }
        for(int i= 1;i<cCount;i++){
            cout << "Courses: " << courses[i] << endl;
        }
     }
};


class University{
    Department *d[10];
    int dcount;
    public: 
     University(Department *da){
        dcount = 0;
        d[dcount++] = da;
     }

     void display (){
        d[0]->displayy();
     }
};
int main(){
    cout << "Running " << endl;
    Department d1;
    d1.setDeptName("Software Engineering");
    string fac1[] = {"Prof. Fahad", "Sir Ali", "Mam Zoha"};
    d1.setFaculty(fac1, 3);
    string std1[] = {"hamza", "arsalan", "Numan", "Arham"};
    d1.setStudent(std1, 4);
    University u(&d1);
    u.display();
    return 0;
}