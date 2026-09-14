#include <iostream>
using namespace std;

int main(){
    string string1 = "Mirza ";
    string string2 = "Zain";
    string *str1p = &string1;
    string *str2p = &string2;
    string concatenate = *str1p + *str2p;
    cout << concatenate << endl;
    return 0;
}