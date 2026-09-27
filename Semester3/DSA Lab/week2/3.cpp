#include<iostream>
using namespace std;

int stringSearch(string arr[], int n, string target){
    for(int  i = 0;i<n;i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}


int main(){
    string students[3] = {"Ali","Aayesha","Ahmed"};
    int index = stringSearch(students, 3, "Aayesha");
    cout << "Index: " << index << endl;
    return 0;
}