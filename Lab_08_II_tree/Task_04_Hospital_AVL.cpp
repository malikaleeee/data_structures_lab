#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;

    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

// Right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// Left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

// Insert a value and balance the AVL tree
Node* insert(Node* node, int value) {
    if (node == nullptr)
        return new Node(value);

    if (value < node->key)
        node->left = insert(node->left, value);
    else if (value > node->key)
        node->right = insert(node->right, value);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && value < node->left->key) {
        cout << "LL Rotation at node " << node->key << endl;
        return rightRotate(node);
    }

    // RR Case
    if (balance < -1 && value > node->right->key) {
        cout << "RR Rotation at node " << node->key << endl;
        return leftRotate(node);
    }

    // LR Case
    if (balance > 1 && value > node->left->key) {
        cout << "LR Rotation at node " << node->key << endl;
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && value < node->right->key) {
        cout << "RL Rotation at node " << node->key << endl;
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (root == nullptr) return;

    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

// Display the tree sideways
void displayTree(Node* root, int space = 0) {
    if (root == nullptr) return;

    space += 5;

    displayTree(root->right, space);

    cout << endl;
    for (int i = 5; i < space; i++)
        cout << " ";

    cout << root->key << endl;

    displayTree(root->left, space);
}

// Demonstrate each of the four rotation cases
void testRotation(string caseName, int a, int b, int c) {
    cout << "\nTesting " << caseName << " case:" << endl;

    Node* testRoot = nullptr;
    testRoot = insert(testRoot, a);
    testRoot = insert(testRoot, b);
    testRoot = insert(testRoot, c);

    cout << "Balanced tree (in-order): ";
    inOrder(testRoot);
    cout << endl;
}

int main() {
    Node* root = nullptr;

    int appointments[] = {15, 25, 35, 45, 55, 65, 75};

    cout << "HOSPITAL APPOINTMENT SYSTEM - AVL TREE" << endl;
    cout << "======================================" << endl;

    cout << "\nInserting appointment values:" << endl;

    for (int value : appointments) {
        cout << "Inserting: " << value << endl;
        root = insert(root, value);
    }

    cout << "\nFinal AVL Tree (sideways):" << endl;
    displayTree(root);

    cout << "\nIn-order Traversal: ";
    inOrder(root);
    cout << endl;

    cout << "\nRoot Height: " << getHeight(root) << endl;
    cout << "Root Balance Factor: " << getBalance(root) << endl;

    cout << "\n--- Demonstrating All Four Rotation Cases ---" << endl;

    testRotation("LL", 30, 20, 10);
    testRotation("RR", 10, 20, 30);
    testRotation("LR", 30, 10, 20);
    testRotation("RL", 10, 30, 20);

    return 0;
}