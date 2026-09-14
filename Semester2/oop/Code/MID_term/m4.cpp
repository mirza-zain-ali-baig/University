#include<iostream>
using namespace std;

class Array{
    int *a;
    int size;
    public:
     Array(){
        size = 0;
        a = new int[size];
     }

     Array(int arr[]){
        a = new int[size];
        for(int i = 0;i<size;i++){
            a[i] = arr[i];
        }
     }

     ~Array(){
        delete[] a;
     }
     void input(){
        cout << "Enter the size: ";
        cin >> size;
         for(int i = 0;i<size;i++){
            cout << "Enter the array value for "<< i+1 << ": ";
            cin >> a[i];            
        }
     }
     void print() const {
        for(int i = 0;i<size;i++){
            cout << "A " << i+1 << ": "<< a[i] << endl;
        }
     }
};

int main(){
    Array a;
    a.input();
    a.print();
    return 0;
}