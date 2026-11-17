// ============================================================
//  Data Structure Lab - BSDS-III (Evening) - Lab 08 (Trees)
//  Name    : Anees Ahmad
//  Roll No : 2502491
//  Program : BS Data Science
//  Q1      : Airport Flight Scheduling System - Binary Search Tree
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ---------- Node class: one flight record ----------
class Node {
public:
    int flightNo;
    string destination;
    string departure;
    Node* left;
    Node* right;

    Node(int f, string d, string t) {
        flightNo = f;
        destination = d;
        departure = t;
        left = NULL;
        right = NULL;
    }
};

// ---------- BST class ----------
class FlightBST {
private:
    Node* root;

    Node* insert(Node* node, int f, string d, string t) {
        if (node == NULL)                       // empty spot found
            return new Node(f, d, t);
        if (f < node->flightNo)                 // smaller -> go left
            node->left = insert(node->left, f, d, t);
        else if (f > node->flightNo)            // bigger -> go right
            node->right = insert(node->right, f, d, t);
        else
            cout << "Flight " << f << " already exists!\n";
        return node;
    }

    Node* findMin(Node* node) {                 // left-most node
        while (node != NULL && node->left != NULL)
            node = node->left;
        return node;
    }

    Node* findMax(Node* node) {                 // right-most node
        while (node != NULL && node->right != NULL)
            node = node->right;
        return node;
    }

    Node* remove(Node* node, int f) {
        if (node == NULL) {
            cout << "Flight " << f << " not found, nothing deleted.\n";
            return NULL;
        }
        if (f < node->flightNo)
            node->left = remove(node->left, f);
        else if (f > node->flightNo)
            node->right = remove(node->right, f);
        else {
            // Case 1: leaf node (no child)
            if (node->left == NULL && node->right == NULL) {
                cout << "Case 1 (leaf node): deleting flight " << f << "\n";
                delete node;
                return NULL;
            }
            // Case 2: only one child
            if (node->left == NULL) {
                cout << "Case 2 (one child - right): deleting flight " << f << "\n";
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == NULL) {
                cout << "Case 2 (one child - left): deleting flight " << f << "\n";
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children -> replace with in-order successor
            Node* succ = findMin(node->right);
            cout << "Case 3 (two children): deleting flight " << f
                 << ", replaced by in-order successor " << succ->flightNo << "\n";
            node->flightNo = succ->flightNo;
            node->destination = succ->destination;
            node->departure = succ->departure;
            node->right = removeSilently(node->right, succ->flightNo);
        }
        return node;
    }

    // used only to remove the successor (it has at most a right child)
    Node* removeSilently(Node* node, int f) {
        if (node == NULL) return NULL;
        if (f < node->flightNo)
            node->left = removeSilently(node->left, f);
        else if (f > node->flightNo)
            node->right = removeSilently(node->right, f);
        else {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        return node;
    }

    void printRecord(Node* n) {
        cout << "  " << left << setw(8) << n->flightNo
             << setw(16) << n->destination << n->departure << "\n";
    }

    void inorder(Node* n) {                     // Left - Root - Right
        if (n == NULL) return;
        inorder(n->left);
        printRecord(n);
        inorder(n->right);
    }

    void preorder(Node* n) {                    // Root - Left - Right
        if (n == NULL) return;
        printRecord(n);
        preorder(n->left);
        preorder(n->right);
    }

    void postorder(Node* n) {                   // Left - Right - Root
        if (n == NULL) return;
        postorder(n->left);
        postorder(n->right);
        printRecord(n);
    }

    int count(Node* n) {
        if (n == NULL) return 0;
        return 1 + count(n->left) + count(n->right);
    }

    int height(Node* n) {                       // levels: empty = 0, leaf = 1
        if (n == NULL) return 0;
        int lh = height(n->left);
        int rh = height(n->right);
        return 1 + (lh > rh ? lh : rh);
    }

    void printTree(Node* n, string indent, string label) {
        if (n == NULL) return;
        cout << indent << label << n->flightNo << " (" << n->destination << ")\n";
        printTree(n->left,  indent + "      ", "L---- ");
        printTree(n->right, indent + "      ", "R---- ");
    }

public:
    FlightBST() { root = NULL; }

    void insert(int f, string d, string t) { root = insert(root, f, d, t); }

    void search(int f) {
        Node* cur = root;
        int steps = 0;
        while (cur != NULL) {
            steps++;
            if (f == cur->flightNo) {
                cout << "Flight " << f << " FOUND after " << steps << " comparisons -> "
                     << cur->destination << " at " << cur->departure << "\n";
                return;
            }
            if (f < cur->flightNo) cur = cur->left;
            else cur = cur->right;
        }
        cout << "Flight " << f << " NOT FOUND in the schedule.\n";
    }

    void remove(int f) { root = remove(root, f); }

    void header() {
        cout << "  " << left << setw(8) << "Flight" << setw(16) << "Destination" << "Departure\n";
        cout << "  ---------------------------------\n";
    }
    void inorder()   { header(); inorder(root); }
    void preorder()  { header(); preorder(root); }
    void postorder() { header(); postorder(root); }

    void showMinMax() {
        if (root == NULL) { cout << "Tree is empty.\n"; return; }
        Node* mn = findMin(root);
        Node* mx = findMax(root);
        cout << "Minimum flight number: " << mn->flightNo << " (" << mn->destination << ")\n";
        cout << "Maximum flight number: " << mx->flightNo << " (" << mx->destination << ")\n";
    }

    int count()  { return count(root); }
    int height() { return height(root); }

    void printTree() { printTree(root, "", "Root: "); }
};

void line(string title) {
    cout << "\n==================================================\n";
    cout << "  " << title << "\n";
    cout << "==================================================\n";
}

int main() {
    cout << "Name: Anees Ahmad | Roll No: 2502491 | BS Data Science\n";
    cout << "Q1 - Airport Flight Scheduling System (BST)\n";

    FlightBST bst;

    line("1) Inserting 13 flight records");
    bst.insert(500, "Dubai",        "08:30");
    bst.insert(300, "London",       "09:15");
    bst.insert(700, "New York",     "10:00");
    bst.insert(200, "Istanbul",     "11:45");
    bst.insert(400, "Doha",         "12:30");
    bst.insert(600, "Toronto",      "13:10");
    bst.insert(800, "Tokyo",        "14:20");
    bst.insert(150, "Jeddah",       "15:00");
    bst.insert(250, "Paris",        "16:40");
    bst.insert(350, "Beijing",      "17:25");
    bst.insert(650, "Kuala Lumpur", "18:05");
    bst.insert(900, "Sydney",       "19:50");
    bst.insert(450, "Riyadh",       "21:15");
    cout << "13 flights inserted.\n\n";
    cout << "BST structure after insertion:\n";
    bst.printTree();

    line("2) Traversals");
    cout << "In-order (sorted by flight number):\n";
    bst.inorder();
    cout << "\nPre-order:\n";
    bst.preorder();
    cout << "\nPost-order:\n";
    bst.postorder();

    line("3) Searching flights");
    bst.search(400);
    bst.search(650);
    bst.search(999);

    line("4) Min / Max, Count, Height");
    bst.showMinMax();
    cout << "Total flights : " << bst.count() << "\n";
    cout << "Tree height   : " << bst.height() << " levels\n";

    line("5) Deleting flights (all 3 cases)");
    bst.remove(150);   // leaf
    bst.remove(600);   // one child (650)
    bst.remove(300);   // two children (200 and 400)

    line("6) Final BST after insertion and deletion");
    bst.printTree();
    cout << "\nIn-order after deletion:\n";
    bst.inorder();
    cout << "\n";
    bst.showMinMax();
    cout << "Total flights : " << bst.count() << "\n";
    cout << "Tree height   : " << bst.height() << " levels\n";

    return 0;
}
