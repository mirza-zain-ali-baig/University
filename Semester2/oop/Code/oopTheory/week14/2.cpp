#include<iostream>
using namespace std;


template <typename T, typename T2>

class User{
    protected:
        T id;
        T2 name;
    public:
        User(T uid, T2 uname): id(uid), name(uname) {
        }

        void display(){
            cout << "User ID: " << id << endl;
            cout << "User Name: " << name << endl;
        }
         

};

int main(){

    User<int, string> user1(1, "Alice");
    user1.display();
    return 0;

}