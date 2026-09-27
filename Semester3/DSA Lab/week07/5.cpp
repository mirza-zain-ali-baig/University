// Stack

#include<iostream>
using namespace std;

#define MAXelements 100

class Stack{
    char stack[MAXelements];
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

    void push(char value){
        if(isFull()){
            cout << "Stack Overflow." << endl;
            return;
        }
        stack[++top] = value;
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
        return stack[top];
    }

    void display(){
        for(int i = top;i>=0;i--){
            cout << stack[i] << " "; 
        }
        cout << endl;
    }

    int precedence(char op){
        if(op == '+' || op == '-'){
            return 1;
        }
        else if(op == '*' || op == '/'){
            return 2;
        }
        return -1;
    }

    string reverseInput(string input){
        string reverse = "";
        for(int i = input.length() -1;i>=0;i--){
            reverse += input[i];
        }
        return reverse;
    }

    string parenthesisSwap(string input){
        char current;
        string swappedString = "";
        for(int i = 0;i<input.length();i++){
            current = input[i];
            if(current == '('){
                current = ')';
            }
            else if(current == ')'){
                current = '(';
            }
            swappedString += current; 
        }
        return swappedString;
    }


    string postfixConverter(string input){
        string postfix = "";
        for(int i = 0;i<input.length();i++){
            char current = input[i];
            if((current >= 'A' && current <= 'Z') || (current>= 'a' && current <= 'z')){
                postfix += current;
            }
            else if(current == '-' || current == '+' || current == '*' || current == '/'){
                while(top != -1 && precedence(stack[top])>=precedence(current)){   
                        postfix += stack[top];
                        pop();
                     }
                     push(current);
            }
            else if(current == '('){
                push(current);
            }
            else if(current == ')'){
                while(stack[top] != '('){
                    postfix += stack[top];
                    pop();
                }
                pop();
            }
        }
        while(top != -1){
            postfix += stack[top--];
        }
        return postfix;
    }

    string prefixConverter(string input){

        // We created the seperate functions for each task to make code clean and understandable
        string reverseInp = reverseInput(input);
        string swapped = parenthesisSwap(reverseInp);
        string postfix = postfixConverter(swapped);
        string output = reverseInput(postfix);
        return output;
    }
};

int main(){
    Stack s1;
    string input = "(A+B)*(C+D)";
    string output = s1.prefixConverter(input);
    cout << "Prefix String: " << output << endl;
    return 0;
}