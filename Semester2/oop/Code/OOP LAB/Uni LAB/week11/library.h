#include<iostream>
#include "books.h"
using namespace std;

class Library{
    private:
     int count;
     Book *books[50];
    public:
     Library();
     void addBook(Book *b);
     void removeBook(string t);
     void searchBook(string t);
};