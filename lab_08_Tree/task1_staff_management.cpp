// Lab 08 - Task 1: University Staff Management System
// Part A: General Binary Tree (staff names)
// Part B: Binary Search Tree (unique staff IDs)

#include <iostream>
#include <string>
#include <limits>
using namespace std;

/* ===================== PART A: GENERAL BINARY TREE ===================== */

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string n) {
        name = n;
        left = nullptr;
        right = nullptr;
    }
};

class StaffTree {
private:
    Node* root;

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // Prints one staff member with their left and right children (pre-order walk)
    void displayNode(Node* node) {
        if (node == nullptr) return;
        cout << "  " << node->name << "  -->  Left: "
             << (node->left  ? node->left->name  : "NULL")
             << "  |  Right: "
             << (node->right ? node->right->name : "NULL") << endl;
        displayNode(node->left);
        displayNode(node->right);
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->name << " | ";
        inorder(node->right);
    }

public:
    StaffTree() { root = nullptr; }
    ~StaffTree() { destroy(root); }

    // Builds a tree of 8 staff members (names are NOT in any sorted order)
    void createTree() {
        root = new Node("Dr. Ahmed");
        root->left = new Node("Ms. Sana");
        root->right = new Node("Mr. Bilal");

        root->left->left = new Node("Mr. Usman");
        root->left->right = new Node("Ms. Hina");

        root->right->left = new Node("Dr. Zara");
        root->right->right = new Node("Mr. Omar");

        root->left->left->left = new Node("Ms. Ayesha");
    }

    void display() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return;
        }
        displayNode(root);
    }

    void showInorder() {
        cout << "  In-order of general tree: ";
        inorder(root);
        cout << endl;
    }
};

/* ===================== PART B: BINARY SEARCH TREE ===================== */

class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        id = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;
    bool showCase = true;   // print which deletion case happened

    BSTNode* insert(BSTNode* node, int value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new BSTNode(value);
        }
        if (value < node->id)
            node->left = insert(node->left, value, inserted);
        else if (value > node->id)
            node->right = insert(node->right, value, inserted);
        // equal -> duplicate, inserted stays false, tree unchanged
        return node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    BSTNode* remove(BSTNode* node, int value, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (value < node->id) {
            node->left = remove(node->left, value, deleted);
        }
        else if (value > node->id) {
            node->right = remove(node->right, value, deleted);
        }
        else {
            deleted = true;

            // Case 1 (leaf) and Case 2 (one child, right only)
            if (node->left == nullptr) {
                if (showCase) {
                    if (node->right == nullptr)
                        cout << "  [Case: leaf node]" << endl;
                    else
                        cout << "  [Case: node with one child]" << endl;
                }
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2 (one child, left only)
            if (node->right == nullptr) {
                if (showCase) cout << "  [Case: node with one child]" << endl;
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children -> use in-order successor
            if (showCase) cout << "  [Case: node with two children]" << endl;
            BSTNode* successor = findMin(node->right);
            node->id = successor->id;
            bool dummy = false;
            bool saved = showCase;
            showCase = false;   // do not print a case line for the successor removal
            node->right = remove(node->right, successor->id, dummy);
            showCase = saved;
        }
        return node;
    }

    // Visits nodes and counts comparisons
    bool search(BSTNode* node, int value, int& visits) {
        while (node != nullptr) {
            visits++;
            if (value == node->id) return true;
            if (value < node->id) node = node->left;
            else node = node->right;
        }
        return false;
    }

    void inorder(BSTNode* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    BSTNode* copyTree(BSTNode* node) {
        if (node == nullptr) return nullptr;
        BSTNode* n = new BSTNode(node->id);
        n->left = copyTree(node->left);
        n->right = copyTree(node->right);
        return n;
    }

    void destroy(BSTNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() { root = nullptr; }

    // Copy constructor: makes a FRESH, independent copy of a BST
    BST(const BST& other) { root = copyTree(other.root); }

    BST& operator=(const BST&) = delete;

    ~BST() { destroy(root); }

    bool insertId(int value) {
        bool inserted = false;
        root = insert(root, value, inserted);
        return inserted;
    }

    bool searchId(int value, int& visits) {
        visits = 0;
        return search(root, value, visits);
    }

    bool deleteId(int value) {
        bool deleted = false;
        root = remove(root, value, deleted);
        return deleted;
    }

    void display(const string& label = "BST (ascending)") {
        cout << label << ": ";
        if (root == nullptr) cout << "(empty)";
        else inorder(root);
        cout << endl;
    }
};

/* ===================== HELPER FUNCTIONS ===================== */

// Safe integer input (re-asks if user types letters)
int readInt(const string& prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a whole number: ";
    }
    return x;
}

void insertAndReport(BST& tree, int id) {
    if (tree.insertId(id))
        cout << "  Inserted " << id << endl;
    else
        cout << "  Duplicate ID " << id << " rejected (tree unchanged)." << endl;
}

void searchAndReport(BST& tree, int id) {
    int visits = 0;
    bool found = tree.searchId(id, visits);
    cout << "  Search " << id << ": " << (found ? "FOUND" : "NOT FOUND")
         << " | node visits = " << visits << endl;
}

BST makeOriginalBST() {
    BST t;
    int ids[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : ids) t.insertId(id);
    return t;   // copy elision / copy constructor gives a valid independent tree
}

/* ============================== MAIN ============================== */

int main() {
    cout << "=========== PART A: GENERAL BINARY TREE ===========" << endl;
    StaffTree staff;
    staff.createTree();
    staff.display();
    staff.showInorder();

    cout << "\n=========== PART B: BINARY SEARCH TREE ===========" << endl;
    BST tree;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    cout << "Inserting initial IDs: 48, 28, 68, 18, 38, 58, 78" << endl;
    for (int id : initial) tree.insertId(id);
    tree.display("Initial BST");

    // Requirement 5: three more IDs from user
    cout << "\n--- Enter three additional staff IDs ---" << endl;
    for (int i = 1; i <= 3; i++) {
        int id = readInt("Enter staff ID " + to_string(i) + ": ");
        insertAndReport(tree, id);
    }
    tree.display("BST after user insertions");

    // Requirement 6 & 7: searching
    cout << "\n--- Search tests ---" << endl;
    cout << "Existing ID (38):" << endl;
    searchAndReport(tree, 38);
    cout << "Missing ID (45):" << endl;
    searchAndReport(tree, 45);
    cout << "ID smaller than all registered IDs (1):" << endl;
    searchAndReport(tree, 1);

    int s = readInt("\nEnter a staff ID to search: ");
    searchAndReport(tree, s);

    // Requirement 8: test each deletion case on a FRESH copy of the original BST
    cout << "\n--- Deletion tests (each on a fresh copy of the original BST) ---" << endl;

    {
        BST t = makeOriginalBST();
        t.display("Fresh copy        ");
        cout << "Delete 18 (leaf):" << endl;
        t.deleteId(18);
        t.display("After deleting 18 ");
    }
    {
        BST t = makeOriginalBST();
        t.insertId(10);   // 18 now has exactly ONE child (10)
        t.display("Fresh copy + 10   ");
        cout << "Delete 18 (one child):" << endl;
        t.deleteId(18);
        t.display("After deleting 18 ");
    }
    {
        BST t = makeOriginalBST();
        t.display("Fresh copy        ");
        cout << "Delete 28 (two children):" << endl;
        t.deleteId(28);
        t.display("After deleting 28 ");
    }
    {
        BST t = makeOriginalBST();
        cout << "Delete 48 (root, two children):" << endl;
        t.deleteId(48);
        t.display("After deleting 48 ");
    }

    // Delete an ID entered by the user from the main tree
    cout << "\n--- Delete from main tree ---" << endl;
    tree.display("Before deletion");
    int d = readInt("Enter a staff ID to delete: ");
    if (tree.deleteId(d))
        cout << "  ID " << d << " deleted." << endl;
    else
        cout << "  ID " << d << " not found. Nothing deleted." << endl;

    // Requirement 9
    tree.display("Remaining staff IDs (in-order, ascending)");

    // Requirement 10
    cout << "\n--- Why in-order is sorted only for a BST ---" << endl;
    cout << "A general binary tree has no rule about where values go, so its in-order\n"
            "output follows the shape of the tree, not the size of values (see the\n"
            "staff names in Part A: they are not alphabetical). In a valid BST every\n"
            "value in the left subtree is smaller than the node and every value in\n"
            "the right subtree is larger. In-order visits Left, Root, Right, so it\n"
            "always prints smaller values, then the node, then larger values, which\n"
            "gives ascending order." << endl;

    return 0;
}