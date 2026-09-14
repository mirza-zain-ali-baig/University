#include <iostream>
using namespace std;
int findMax(int *a, int *b){
    int max;
    if (a> b){
        max = *a;
    }
    else{
        max = *b;
    }
    return max;
}

int main(){
    int a = 4 ,b = 5;
    cout << findMax(&a,&b) << endl; 
    //cout << *findMax(&a,&b) << endl; 
}