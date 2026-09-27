#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};
Node* createNode(int value)
{
    Node* temp = new Node();

    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

Node* insert(Node* root, int value)
{
    Node* newNode = createNode(value);

    if(root == NULL)
    {
        root = newNode;
        return root;
    }

    Node* current = root;
    Node* parent = NULL;

    while(current != NULL)
    {
        parent = current;

        if(value < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if(value < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    return root;
}

bool search(Node* root, int key)
{
    Node* current = root;

    while(current != NULL)
    {
        if(current->data == key)
        {
            return true;
        }

        if(key < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return false;
}

int main()
{
    Node* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    if(search(root, 40))
    {
        cout << "Found";
    }
    else
    {
        cout << "Not Found";
    }

    return 0;
}

