#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string folder;
    Node* left;
    Node* right;

    Node(string name) {
        folder = name;
        left = nullptr;
        right = nullptr;
    }
};

// In-order: Left, Root, Right
void inOrder(Node* root) {
    if (root == nullptr) return;

    inOrder(root->left);
    cout << root->folder << " ";
    inOrder(root->right);
}

// Pre-order: Root, Left, Right
void preOrder(Node* root) {
    if (root == nullptr) return;

    cout << root->folder << " ";
    preOrder(root->left);
    preOrder(root->right);
}

// Post-order: Left, Right, Root
void postOrder(Node* root) {
    if (root == nullptr) return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->folder << " ";
}

int main() {
    // Create file explorer tree
    Node* root = new Node("Computer");

    root->left = new Node("Documents");
    root->right = new Node("Downloads");

    root->left->left = new Node("Assignments");
    root->left->right = new Node("Projects");

    root->right->left = new Node("Images");
    root->right->right = new Node("Videos");

    cout << "COMPUTER FILE EXPLORER" << endl;
    cout << "======================" << endl;

    cout << "\nIn-order Traversal: ";
    inOrder(root);

    cout << "\nPre-order Traversal: ";
    preOrder(root);

    cout << "\nPost-order Traversal: ";
    postOrder(root);

    cout << endl;

    return 0;
}