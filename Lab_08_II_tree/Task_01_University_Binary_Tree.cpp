#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string value) {
        name = value;
        left = nullptr;
        right = nullptr;
    }
};

void displayTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    cout << "Member: " << root->name << endl;

    cout << "Left Child: ";
    if (root->left != nullptr)
        cout << root->left->name << endl;
    else
        cout << "None" << endl;

    cout << "Right Child: ";
    if (root->right != nullptr)
        cout << root->right->name << endl;
    else
        cout << "None" << endl;

    cout << "----------------------" << endl;

    displayTree(root->left);
    displayTree(root->right);
}

int main() {
    Node* root = new Node("University Head");

    root->left = new Node("Computer Science");
    root->right = new Node("Business Department");

    root->left->left = new Node("Artificial Intelligence");
    root->left->right = new Node("Software Engineering");

    root->right->left = new Node("Accounting");
    root->right->right = new Node("Marketing");

    root->left->left->left = new Node("Data Science");

    cout << "UNIVERSITY DEPARTMENT HIERARCHY" << endl;
    cout << "================================" << endl;

    displayTree(root);

    return 0;
}