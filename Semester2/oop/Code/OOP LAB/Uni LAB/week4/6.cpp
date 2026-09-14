#include <iostream>
using namespace std;

class Cat{
    string name;
    string catOwner;
    double weight;
    public:

     // Constructors
     Cat(){
      name = "Null";
      catOwner = "Null";
      weight = 0;
     }
     Cat(string n, string c, double w){
        name = n;
        catOwner = c;
        weight = w;
     }

     void change(string owner){  // member function to change
        catOwner = owner;
     }
};

int main(){
    string name;
    string catOwner;
    double weight;
    cout << "Enter CAt Details(name,cat Owner, Weight): ";
    cin >> name >> catOwner >> weight;
    Cat c1(name,catOwner,weight);
    cout << "Cat NAme, Cat Owner, and Cat Weight: " << name << catOwner << weight << endl;
    c1.change("Okay");
    cout << "Cat NAme, Cat Owner, and Cat Weight: " << name << catOwner << weight << endl;
    
    return 0;
}