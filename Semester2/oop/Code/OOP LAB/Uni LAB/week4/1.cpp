#include<iostream>
#include<string>
using namespace std;
class person {
    private:
        string name;
        int age;
        float CGPA;
    public:
        person() //default constructor
        {
        name = " ";
        age = 0;
        CGPA = 0.0;
        }
    person(int a) //parameterized constructor with same name i.e constructor   overloading
        {
        age = a;
        }
    void setAge(int a) {
        if (a > 0)
        age = a;
    }
    int getAge()
        {
        return age;
        }
};

int main(){
    person p1;
    cout << p1.getAge();
}