#include <iostream>
using namespace std;

// Node structure
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Insert function
Node* insert(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

// Search function
bool search(Node* root, int key) {
    if (root == NULL)
        return false;

    if (root->data == key)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Main function
int main() {
    Node* root = NULL;

    // Insert roll numbers
    root = insert(root, 101);
    root = insert(root, 102);
    root = insert(root, 99);
    root = insert(root, 120);

    // Search roll numbers
    if (search(root, 102))
        cout << "Roll number found\n";
    else
        cout << "Roll number not found\n";

    if (search(root, 105))
        cout << "Roll number found\n";
    else
        cout << "Roll number not found\n";

    return 0;
}