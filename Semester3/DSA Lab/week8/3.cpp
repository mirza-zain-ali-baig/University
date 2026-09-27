#include<iostream>
using namespace std;
class Node{
    public:
     int data;
     Node* left;
     Node* right;
    Node(int value){
        data = value;
        left = NULL;
        right == NULL;
    }
};
class BST{
    Node* insert(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else {
        // Duplicate value found → do nothing
        cout << "Duplicate value " << key << " not inserted\n";
    }

    return root;
}
};


int main(){
    BST s1;
    return 0;
}