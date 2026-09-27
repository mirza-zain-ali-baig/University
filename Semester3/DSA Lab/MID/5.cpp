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

class LinkedList{
    Node* head;
    public:
    LinkedList(){
        head = NULL;
    }

    void insertAtStart(int value){
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int value){
        Node* newNode = new Node(value);
        
        if(head == NULL){
            head = newNode;
            return;
        }
        Node *temp = head;

        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;

    }
     void reverse(){
     Node* pre = NULL;
     Node* nextNode;
     Node*current = head;

     while(current != NULL){
        nextNode = current->next;
        current->next = pre;
        pre = current;
        current = nextNode;
     }
     head = pre;
     }

     void display(){
        if(head == NULL){
            cout << "LIST is empty. ";
        }
            Node *temp = head;
            while(temp != NULL){
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
     }
};
int main(){
    LinkedList l1;
    l1.insertAtEnd(2);
    l1.insertAtEnd(5);
    l1.insertAtEnd(8);

    l1.display();

    l1.reverse();
    l1.display();

    return 0;
}