#include <iostream>
using namespace std;
int fibonanci(int n ){
    if (n<=1){
        return n;
    }
    else{
        return fibonanci(n-1)+fibonanci(n-2);
    }    
}
int main(){
    int limit;
    cout << "Enter the limit: ";
    cin >> limit;
    for (int i = 0; i<=limit;i++){
        cout << fibonanci(i) << " ";
    }
    return 0;
}