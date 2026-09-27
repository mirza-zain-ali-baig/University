// Balanced Parentheses: Write a function that checks if every opening bracket {[( has a
// matching closing bracket )]}.

#include<iostream>
using namespace std;

class Node{
    public:
     char data;
     Node* next;
     Node(int value){
        data = value;
        next = NULL;
     }
};

class Stack{
    Node *top;
    public:
     Stack(){
        top = NULL;
     }
     bool isEmpty(){
        return top == NULL;        
     }
     void push(char value){
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
     }
     void pop(){
        if(isEmpty()){
            cout << "Stack Underflow" << endl;
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
     }

     string bracketChecker(string sequence){
        for(int i = 0;i<sequence.length(); i++){
            char current = sequence[i];
            if(current == '[' || current == '{' || current == '('){
                push(current);
            }
            else if(current == ')' || current == '}' || current == ']'){
                if (top == NULL) return "Rejected: Sequence is Wrong";
                char lastover = top->data;
                if((lastover == '{' && current == '}') || (lastover == '[' && current == ']') || (lastover == '(' && current == ')')){
                 pop();
               }
            }
        }
        if(isEmpty()){
         return "Accepted: Sequence is Correct.";
        }
        else{
         return "Rejected: Sequence is Wrong.";
        }        
     }
};

int main(){
    string input = "{{{()}}}{}(()){}[]";
    Stack s;
    cout << s.bracketChecker(input) << endl;
    return 0;
}