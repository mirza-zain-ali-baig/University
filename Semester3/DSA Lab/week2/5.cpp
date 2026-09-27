#include<iostream>
using namespace std;
int main(){
    int arr[3][2]= {{1,2},{0,4},{5,3}};
    int target = 3;
    int row,column;
    for(int i = 0;i<3;i++){
        for(int j =0;j<2;j++){
            if(arr[i][j] == target){
                row = i;
                column = j;
                break;
            }
        }
        cout << "OK" << endl;
    }
    cout << row << " " << column << endl;
    return 0;
}

// O(1)