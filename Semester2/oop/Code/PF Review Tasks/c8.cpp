#include <iostream>
using namespace std;

void countVowels(int &count, string &str){
    string vowels = "aeiouAEIOU";
    cout << str.length() << endl;
    for ( int i = 0; i< str.length();i++){
        for(int j = 0;j<10;j++){
            if (str[i] == vowels[j]){
                count++;
            }
        }

    }    
}

int main(){
    string str;
    int count = 0;
    cout << "Enter a string: ";
    cin >> str;
    countVowels( count, str);
    cout << "Vowels are: " << count << endl;
}