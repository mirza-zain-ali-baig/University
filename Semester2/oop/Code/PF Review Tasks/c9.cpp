#include <iostream>
using namespace std;
int power(int *a, int *p){
    if ( *p <=1){
        return 1;
    }
    else{
        return (*a) * power(a,*p--) ;
    }
}


int main(){
    int n,p;
    cout << "Enter a number: ";
    cin >> n;
    cout << "Power number: ";
    cin >> p;
    cout << power(&n, &p);
    return 0;
}