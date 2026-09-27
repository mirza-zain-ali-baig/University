#include<iostream>
using namespace std;

int linearSearchCounter(int arr[],int n, int target){
    int count =0;
    for(int i = 0;i<n;i++){
        if(arr[i]==target){
            count++;
        }
    }
    return count;
}

int main(){
    int arr[5] = {2,4,1,5,5};
    int n = 5;
    int count = linearSearchCounter(arr,5,5);
    if( count != 0){
        cout <<"Count: " << count << endl;
    }
    else{
        cout << "Target Number not found. " << endl;
    }
    return 0;
}