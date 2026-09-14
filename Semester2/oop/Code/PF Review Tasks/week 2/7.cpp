// Copy one string into another using pointers
#include <iostream>
using namespace std;
int main(){
   string name = "Zain";
   string *ptr = &name;
   string str2;
   string *str2ptr = &str2;
   *str2ptr = *ptr;
   cout << *str2ptr << endl;
   return 0;
}
