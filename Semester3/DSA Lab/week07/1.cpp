// Stack

#include<iostream>
using namespace std;

#define MAXelements 5

class Stack{
    int arr[MAXelements];
    int top;
   public:
    Stack(){
        top = -1;
    }

    bool isFull(){
        return top == MAXelements -1;
    }
    bool isEmpty(){
        return top == -1;
    }

    void push(int value){
        if(isFull()){
            cout << "Stack Overflow." << endl;
            return;
        }
        arr[++top] = value;
    }

    void pop(){
        if(isEmpty()){
            cout << "Stack underflow" << endl;
            return;
        }
        top--;
    }

    int peek(){
        if(isEmpty()){
            cout << "Stack is Empty. " << endl;
            return -1;
        }
        return arr[top];
    }

    void display(){
        for(int i = top;i>=0;i--){
            cout << arr[i] << " "; 
        }
        cout << endl;
    }

};

int main(){
    Stack s;
    s.push(2);
    s.push(44);
    s.push(66);

    s.display();

    s.pop();

    cout << "Top Element after deletion " << s.peek() << endl;
    cout << "Disp[l]ay all elements: " << endl;
    s.display();

}