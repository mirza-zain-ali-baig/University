#include <iostream>
using namespace std;
void countVowels(char* name){
    int count = 0;
    while(*name !=0 ){
        char ch = tolower(*name);
        if(ch == 'a' || ch == 'e' || ch == 'o' || ch == 'i' || ch == 'u'){
            count++;
        }
        name++;
    }
    cout << count << endl;
}
int main(){
    char name[] = "Mirza Zain";
    countVowels(name);
}