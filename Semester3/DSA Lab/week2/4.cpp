#include<iostream>
using namespace std;
int main(){
    int arr[5] = {2,2,2,1,2};
    int target = 2, count = -1;
    int indices[5];
    for(int i = 0;i<5;i++){
        if(arr[i] == target){
            indices[++count] = i;
        }
    }
    cout << "Indices: " << count << endl;
    for(int i = 0;i<count+1;i++){
        cout << indices[i] << endl;
    }
    return 0;
}