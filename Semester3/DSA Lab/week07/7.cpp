
#include<iostream>
using namespace std;

class Stack{
    char stack[100];
    int top;
    public:
     Stack(){
        top = -1;
     }

     bool isEmpty(){
        return top ==-1;
     }

     void push(char value){
        stack[++top] = value;
     }
     void pop(){
        top--;
     }

     int precedenceAlgorithm(char op1){
        if (op1 == '+' || op1 == '-'){
            return 1;
        }
        else if( op1 == '*' || op1 == '/'){
            return 2;
        }
        else if(op1 == '^' ){
            return 3;
        }
        else if(op1 == '('){
            return 0;
        }
        return -1;
     }

     string converter(string input){
        string postfix = "";
        for(int i = 0;i<input.length();i++){
            char current = input[i];
            if((current >= 'A' && current <= 'Z') || (current>= 'a' && current <= 'z')){
                postfix += current;
            }
            else if(current == '-' || current == '+' || current == '*' || current == '/' || current == '^'){
                while(top != -1 && precedenceAlgorithm(stack[top])>=precedenceAlgorithm(current)){   
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
        while(!isEmpty()){
            postfix += stack[top];
            pop();
        }
        return postfix;
     }
};

int main(){
    string input = "((A+B)*C-(D-E))^(F+G)";
    Stack s;
    cout << s.converter(input) << endl;

    return 0;
}