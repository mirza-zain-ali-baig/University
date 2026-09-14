#include<iostream>
#include "library.h"


int main(){
    Book b1("C++" , "Thomas", 1000);
    Library l1;

    l1.addBook(&b1);
    b1.setTitle("A++");
    l1.searchBook("C++");
    return 0;
}