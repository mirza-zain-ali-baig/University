#include <iostream>
#include <cstring>
using namespace std;
int main(){
    // int arr[] = {1,2,3};
    // cout << arr << endl; // it shhows the address of 0 index

    string array = "123";
    cout << sizeof(array) << endl;
    cout << array.length() << endl;
    // sizeof(  ) => return value in bytes always
    // string is a object, it takes: 
        // On 32-bit system → often 4 bytes
        // On 64-bit system → often 24 or 32 bytes


    // C-Strings
    char cArr[] = {'1','2', '\0'};
    cout << sizeof(cArr) << endl; // char takes only 1 byte for every 1 character, 3 character = 3 bytes
    cout << strlen(cArr) << endl; // \0 is hidden for the compiler means array end here that's why it not count as a char
    return 0;
}