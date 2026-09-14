// Define a structure Book with fields: title, author, and price.
//  Write a function displayExpensiveBooks(Book arr[], int n, float
// minPrice) that prints all books whose price is greater than minPrice.
//  Call the function from main() after taking input.

#include <iostream>
using namespace std;
struct Book{
    string title;
    string authorName;
    int price;
};

void displayExpensiveBooks(Book arr[], int n, float minPrice){
    cout << "Expensive Book details are: ";
    int check = 0;
    for(int i = 0;i<n;i++){
        if( arr[i].price > minPrice){
            cout << "Book Name: " << arr[i].authorName << endl;
            cout << "Book Title: " << arr[i].title << endl;
            cout << "Book Price: " << arr[i].price << endl;
            check = 1;
        }
    }
    if(check == 0){
        cout << "Not expensive book then min Price.";
    }

}
int main(){
    int n;
    float minPrice;
    cout << "Enter the number of books: ";
    cin >> n;
    Book arr[n];
    cout << "Enter the min. price of book: ";
    cin >> minPrice;
    for(int i = 0;i<n;i++){
        cout << "Enter book details for " << i << " : "<< endl;
        cout << "Enter the book title: ";
        cin >> arr[i].title;
        cout << "Enter the Author name: ";
        cin >> arr[i].authorName;
        cout << "Enter the book price: ";
        cin >> arr[i].price;

    }
    displayExpensiveBooks(arr, n, minPrice);

}