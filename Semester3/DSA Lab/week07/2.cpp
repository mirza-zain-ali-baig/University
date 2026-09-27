// Stack using List

#include<iostream>
using namespace std;
class Node{
    public:
    int data;
    Node *next;
     Node(int value){
        data = value;
        next = NULL;
     }
};
class Stack{
    Node* top;
    public:
     Stack(){
        top = NULL;
     }

     void push(int value){
        Node *newNode = new Node(value);
        newNode->next = top;
        top = newNode;
     }

     bool isEmpty(){
        return top == NULL;
     }

     int peek(){
        if(isEmpty()){
            cout << "Satck is Empty." << endl;
            return -1;
        }
        return top->data;
     }
     void pop(){
        if(isEmpty()){
            cout << "Stack underflow" << endl;
            return;
        }
        Node *temp = top;
        top = top->next;
        delete temp;
     }

     void display(){
            for( Node* t = top;t != NULL;t = t->next){
                cout << t->data << " " << endl;
            }
            cout << " NULL " << endl;
     }
};// Balanced Parentheses: Write a function that checks if every opening bracket {[( has a
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
}// Infix → Postfix Conversion: Convert infix expression (A+B)*C into postfix form A B +
// C *.
// Hint: Use a stack for operators.
// Pop from the stack when precedence is higher or equal before pushing a new operator

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
        else if( op1 == '*' && op1 == '/'){
            return 2;
        }
        else if(op1 == '^' ){
            return 3;
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
            else if(current == '-' || current == '+' || current == '*' || current == '/'){
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
        while(top != -1){
            postfix += stack[top--];
        }
        return postfix;
     }
};

int main(){
    string input = "(A+B)*C";
    Stack s;
    cout << s.converter(input) << endl;

    return 0;
}// Stack

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
}#include<iostream>
using namespace std;

#define MAXelements 100

class Stack{
    char arr[MAXelements];
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

    int postfixSolver(string input){
        int result = 0;
        for(int i = 0;i<input.length();i++){
            char current = input[i];
            if(current != '+' && current != '*' && current != '-' && current != '*'){
                push(current);
            }
            else{
                int num1 = arr[top] - '0';
                pop();
                int num2 = arr[top] - '0';
                pop();

                if(current == '+'){
                    result = num1+num2;
                    push(result + '0');
                }
                else if(current == '-'){
                    result = num1-num2;
                    push(result + '0');
                }
                else if(current == '*'){
                    result = num1*num2;
                    push(result + '0');
                }
                else if(current == '/'){
                    result = num1/num2;
                    push(result + '0');
                }
            }
        }

        int output = arr[top] - '0';
        return output;
    }

};

int main(){
    Stack s1;
    string input = "23+5*";
    cout << "After Evaluation:" << s1.postfixSolver(input);
}
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
}#include<iostream>
using namespace std;
int main(){
    char a = '2';
    int aa = a - '0';
    cout << aa+2 << endl;
}