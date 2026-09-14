// sahllow copy: it's problem
// when 1 object is changed it's also changed the other object members after copy constructor applied

#include <iostream>
using namespace std;
// class Shallow{
//  int *a;
//  int size;
//  int gpa;
//  public:
//   Shallow(int s, float g){
//     size = s;
//     a = new int[size];
//     for(int i = 0;i<size;i++){
//       a[i] = i+1;
//     }
//   }
//   void changeP(int v){
//     a[0] = v;
//   }
//   void display(){
//     cout << a[0] << endl;
//   }
// };
// int main(){
//   Shallow s1(2,3.4);
//   s1.display();
//   Shallow s2 = s1;
//   s2.changeP(9);
//   s1.display();
//   return 0;
// }




// Deep Copy

class Deep{
  int *d;
  int size;
  int g;
  public:
   Deep(int s, int g1){
    size = s;
    g = g1;
    d = new int[size];
    for(int i = 0;i<size;i++){
      d[i] = i+1;
    }
   }
   Deep(const Deep &de){
    g = de.g;
    d  = new int[de.size];
    for(int i = 0;i<de.size;i++){
      d[i] = de.d[i];
    }
   }
   void change(int v){
     d[0] = v;
    }
    void display(){
      cout << d[0] << endl;
    }
    ~Deep(){
      cout << d[0] << endl;
     delete[] d;
     cout << d[0] << endl;
     cout << "MEmory deleted." << endl;
    }
};

int main(){
  Deep d1(2,3.5);
  Deep d2(d1);
  d1.display();
  d1.change(2);
  d1.display();
  d2.display();
  return 0;
}


class object{
  string name;
  int id;
  public:
   object(string n, int i){
    name = n;
    id = i;
   }
};