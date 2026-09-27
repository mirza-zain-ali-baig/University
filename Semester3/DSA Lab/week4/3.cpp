#include <iostream>
using namespace std;
int main(){
    // getline(cin, stringVariable, delimiter); // A delimiter is a character that tells getline():
    // “Stop reading input when you see this character.”

    string firstName;
    getline(cin, firstName);
    string lastName;
    getline(cin, lastName);

    // string concatenation
    string fullNAme = firstName + " " + lastName;
    cout << fullNAme << endl;
}