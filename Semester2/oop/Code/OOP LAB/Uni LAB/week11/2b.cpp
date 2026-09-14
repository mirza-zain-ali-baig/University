#include<iostream>
using namespace std;


class RAM{
    int size;
    public:
     RAM(int c): size(c) {}
     void check(){
        cout << "RAM size: " << size << endl;
     }
     void upgrade(int s){
        size = s;
        cout << "RAM upgraded." << endl;
     }
};

class CPU{
    int numberOfCores;
    public:
     CPU(int c): numberOfCores(c) {}
     void check(){
        cout << "CPU cores: " << numberOfCores << endl;
     }
     void upgrade(int n){
        numberOfCores = n;
        cout << "CPU cores Upgraded." << endl;
     }
};

class Storage{
    int storageSize;
    public:
     Storage( int s){
        storageSize = s;
     }

     void check(){
        cout << "Storage size in GB: "<< storageSize << endl;
     }
     void upgrade(int s){
        storageSize = s;
        cout << "Storage upgraded successfully. ";
     }
};

class Computer{
    Storage s1;
    RAM r1;
    CPU c1;
    public:
     Computer(int s, int r, int c): s1(s), r1(r), c1(c) {}
     void ComputerCheck(){
        s1.check();
        r1.check();
        c1.check();
     }
     
};
int main(){
    Computer c1(32, 16, 8);
    c1.ComputerCheck();
    return 0;
}