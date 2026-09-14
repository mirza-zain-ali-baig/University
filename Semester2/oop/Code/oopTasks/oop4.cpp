// 'this' keyword in constructor
#include <iostream>
using namespace std;

class PakCricketer{
    public:
     string name;
     int runs;
     PakCricketer(string name, int runs){
        this->name = name; // 'this' refers to the current object like c1
        this->runs = runs; // 'this' is used to avoid ambiguity (غیر واضح ہونا)
     }
};
int main(){
    PakCricketer c1("Virat Kohli", 100);
    cout << "Name: " << c1.name << endl;
    cout << "Runs: " << c1.runs << endl;

}