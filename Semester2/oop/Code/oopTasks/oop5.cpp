//print function in class
#include <iostream>
using namespace std;
class ToyCar{
    public:
     string color;
     string size;
     string tyres;
     string materials;
     
     // Constructor with parameters

     ToyCar(string color, string size, string tyres, string materials){
        this->color = color;
        this->size = size;
        this->tyres = tyres;
        this->materials = materials;
     }

     void print(string size){
        cout << "Color: " << this->color << "\n" << "Size: " << this->size << "\n" << "Tyres: " << this->tyres << "\n" << "Material: "  << this->materials << endl; 
        cout << this->size << endl;
        // this keyword will check that the object size 
        cout << size << endl;
    }
};
int main(){
    ToyCar c1("White", "medium", "two", "High Quality");
    //c1 is object means actual thing
    c1.print("BLack");
    return 0;
}