#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Node {
public:
    string category;
    Node* left;
    Node* right;

    Node(string value) {
        category = value;
        left = nullptr;
        right = nullptr;
    }
};

void breadthFirstSearch(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;
    q.push(root);

    cout << "Shopping Categories (Level Order):" << endl;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->category << endl;

        if (current->left != nullptr)
            q.push(current->left);

        if (current->right != nullptr)
            q.push(current->right);
    }
}

int main() {
    // Create shopping category tree
    Node* root = new Node("Electronics");

    root->left = new Node("Clothing");
    root->right = new Node("Mobiles");

    root->left->left = new Node("Laptops");
    root->left->right = new Node("Men");

    root->right->left = new Node("Women");
    root->right->right = new Node("Accessories");

    breadthFirstSearch(root);

    return 0;
}