#include<iostream>
using namespace std;
class Book{
    private:
    string title;
    string author;
    int price;
    public:
     Book();
     Book(string t, string a, int p);
     string getTitle();
     void setTitle(string t);
     void displayInfo();
};