#include <iostream>
using namespace std;
void EvenOdd(int *n ){
    if(*n%2==0){
        cout << "Even" << endl;
    }
    else{
        cout << "Odd" << endl;
    }
}
int main(){
    int n ;
    cout << "Enter n: ";
    cin >> n;
    EvenOdd(&n);
    return 0;
}
