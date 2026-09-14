#include <iostream>
using namespace std;

class Box {
public:
    int length;
    Box(int l) { length = l; }

    void compare(Box b) {
        if (length > b.length)
            cout << "First box is larger";
        else
            cout << "Second box is larger";
    }
};

int main() {
    Box b1(10), b2(5);
    b1.compare(b2);   // Passing object as argument
}
