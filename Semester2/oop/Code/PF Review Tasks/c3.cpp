#include <iostream>
using namespace std;
void isPlalindrome(int *a){
    int remainder = 0,reverse = 0,n = *a;
    while(n!=0){
        remainder = n%10;
        reverse = reverse *10 + remainder;
        n = n/10;
    }
    if(*a == reverse){
        cout << "This number is Palindrome." << endl;
    }
    else 
        cout << "It is not Palindrome." << endl;
}
int main(){
    int n;
    cout << "Enter a number: ";
    cin >> n;
    isPlalindrome(&n);
} 