#include <iostream>
using namespace std;
class Book{
    private:
     string bookName;
     int bookPrice;
     int totalPages;
    public:
     Book(){ // Default Constructor
      bookName = "Null";
      bookPrice = 0;
      totalPages = 0;
     }
     Book(string n,int p, int tp){ // parameterised constructor
        bookName = n;
        bookPrice = p;
        totalPages = tp;
     }

    //  void setBookName(string b){
    //     bookName = b;
    //  }
    //  void setBookPrice(int p){
    //     bookPrice = p;
    //  }
    //  void setTotalPages(int tp){
    //     totalPages = tp;
    //  }
    //  string getBookName(){
    //     return bookName;
    //  }
    //  int getBookPrice(){
    //     return bookPrice;
    //  }
    //  int getTotalPages(){
    //     return totalPages;
    //  }

     // Input Function

   //   void input(){
   //      cout << "Enter bookName: ";
   //      cin >> bookName;
   //      cout << "Enter book Price: ";
   //      cin >> bookPrice;
   //      cout << "Enter total Pages: ";
   //      cin >> totalPages;
   //      Book(bookName,bookPrice,totalPages);
   //   }

     // Display function

   //   void display(){
   //      cout << "BookName: " << getBookName() << endl;
   //      cout << "Book Price: " << getBookPrice() << endl;
   //      cout << "Book Total Pages: " << getTotalPages() << endl;
   //   }

   // Display Function for constructor
   void display(){
      cout << "Book Name: " << bookName << endl;
      cout << "Book Price: " << bookPrice << endl;
      cout << "Book Pages: " << totalPages << endl;
   }
};


int main(){
   // Constructor...
   string bookName;
   int bookPrice,totalPages;
   cout << "Enter bookName, bookPrice,and totalPages: ";
   cin >> bookName >> bookPrice >> totalPages;
   Book b1(bookName,bookPrice,totalPages),b2;
   b1.display();
   cout << "Default constructor called when no value pass: " << endl;
   b2.display();
   //  Book b1,b2;
   //  b1.input();
   //  b1.display();
   //  b2.input();
   //  b2.display();
    return 0;
}