#include <iostream>
#include "library.h"
using namespace std;

Library::Library(){
    count = 0;
}


void Library::addBook(Book *b){
    if (count< 50){
        books[count] = b;
        count++;
    }
    else{
        cout << "Library is Full";
    }

}

void Library::removeBook(string t){
    for(int i = 0;i<count; i++){
        if(books[i]->getTitle() == t ){
            cout << "Book Removed Successfully. ";
            for(int j = i;j<count -1;j++){
                books[j] = books[j+1];
            }
            count--; // One Book Removed that's why 
        }
        else{
            cout << "Book not Found";
        }
    }
}

void Library::searchBook(string t){
    for(int i = 0;i<count;i++){
        if(books[i]->getTitle() == t){
            books[i]->displayInfo();
        }
        else{
            cout << "Book not Found. ";
        }
    }
}