#include<iostream>
#include "books.h"
using namespace std;

Book::Book(){
    title = "Null";
    author = "Null";
    price = 0;
}

Book::Book(string t, string a, int p){
    title = t;
    author = a;
    price = p;
}

void Book::displayInfo(){
    cout << "Title: " << title << " , Author: " << author << " , Price: " << price << endl; 
}

string Book::getTitle(){
    return title;
}

void Book::setTitle(string t){
    title = t;
}