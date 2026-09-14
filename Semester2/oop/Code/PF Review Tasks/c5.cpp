#include<iostream>
using namespace std;
// Create a function to find the maximum of three numbers using pass by reference.
void findMax(int &a, int &b, int &c){
    if(a>b && a>c){
        cout << a << " is greater. " << endl;
    }
    else if(b > c && b>a){
        cout << b  << " is greater. " << endl;
    }
    else{
        cout << c << " is greater. " << endl;
    }
}



int main()
{
    int a,b,c;
    cout << "Enter a,b and c: ";
    cin >> a >> b >> c;
    findMax(a,b,c);
    return 0;
    
} 
