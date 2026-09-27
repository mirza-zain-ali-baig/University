#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node *next;

    Node(int d){
        data = d;
        next = NULL;
    }
};

class List{
    Node *head;
    Node *tail;

    public:
     List(){
        head = tail = NULL;
     }

     void pushFront(int value){
        Node *newNode = new Node(value);
        if(head == NULL){
            head = tail = newNode;
            return;
        }
        else{
            newNode->next= head;
            head = newNode;
        }
     }

     void pushBack(int value){

        Node *newNode = new Node(value);
        if(head == NULL){
            head = tail = newNode;
            return;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
     }

     void popFront(){

        if(head == NULL){
            cout << "List is Empty. \n";
            return;
        }

            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;

     }

     void popBack(){

        if(head == NULL){
            cout << "List is empty.\n";
            return;
        }
        Node *temp = head;
        while(temp->next != tail){
            temp = temp->next; 
        }

        temp->next = NULL;
        delete tail;
        tail = temp; 

     }
     void printList(){
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

     }
};

int main(){
    List l1;
    l1.pushFront(1);
    l1.pushFront(2);
    l1.pushFront(3);

    l1.popBack();

    l1.printList();

    return 0;
}