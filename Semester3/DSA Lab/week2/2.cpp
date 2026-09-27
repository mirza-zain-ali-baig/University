#include<iostream>
using namespace std;

int charSearch(char arr[],int n, int target){
    for(int i = 0;i<n;i++){
        if(arr[i]==target){
            return i;
        }
    }
    return 0;
}

int main(){
    char vowels[] = {'o','a','e','i','u'};
    int index = charSearch(vowels,5,'o');
    cout << "You search found at index: " << index << endl;
    return 0;
}