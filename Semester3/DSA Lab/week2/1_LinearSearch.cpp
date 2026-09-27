#include<iostream>
using namespace std;

int linearSearch(int arr[], int size, int target){
    for(int i = 0;i<size;i++){
        if(arr[i]== target){
            return i;
        }
    }
    return -1;
}

// TIme Complexity: Best Case: Big Omega(1), Average Case: Theta(n), Worst Case: O(n)

int main(){
    int size, search;
    int *array = new int[size];
    cout << "Enter the size of an array: ";
    cin >> size;
    for(int i = 0;i<size;i++){
        cout << "Enter the element for index " << i << ": ";
        cin >> array[i];
    }
    cout << "Enter the search: ";
    cin >> search;

    int result = linearSearch(array,size,search);
    if(search != -1){
        cout << "Your Search found at index: " << result << endl;
    }
    else{
        cout << "Your search not found. " << endl;
    }

    return 0;
}