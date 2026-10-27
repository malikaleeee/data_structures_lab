// Lab 08 - Task 2: Hospital and Emergency Inventory Management System
// Menu-driven BST application

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;

    Node(int value) {
        id = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(value);
        }
        if (value < node->id)
            node->left = insert(node->left, value, inserted);
        else if (value > node->id)
            node->right = insert(node->right, value, inserted);
        return node;   // duplicate: nothing changes
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* remove(Node* node, int value, bool& deleted) {
        if (node == nullptr) return nullptr;

        if (value < node->id) {
            node->left = remove(node->left, value, deleted);
        }
        else if (value > node->id) {
            node->right = remove(node->right, value, deleted);
        }
        else {
            deleted = true;
            // Leaf or only a right child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Only a left child
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Two children: copy in-order successor, then delete the successor
            Node* successor = findMin(node->right);
            node->id = successor->id;
            bool dummy = false;
            node->right = remove(node->right, successor->id, dummy);
        }
        return node;
    }

    bool search(Node* node, int value) {
        while (node != nullptr) {
            if (value == node->id) return true;
            node = (value < node->id) ? node->left : node->right;
        }
        return false;
    }

    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) return;
        cout << node->id << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->id << " ";
    }

    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    // Height counted in NODES on the longest root-to-leaf path
    // (empty tree = 0, single node = 1)
    int height(Node* node) {
        if (node == nullptr) return 0;
        int l = height(node->left);
        int r = height(node->right);
        return 1 + (l > r ? l : r);
    }

    void collect(Node* node, vector<int>& out) {
        if (node == nullptr) return;
        collect(node->left, out);
        out.push_back(node->id);
        collect(node->right, out);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() { root = nullptr; }
    ~BST() { destroy(root); }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool isEmpty() { return root == nullptr; }

    bool insertId(int value) {
        bool inserted = false;
        root = insert(root, value, inserted);
        return inserted;
    }

    bool searchId(int value) { return search(root, value); }

    bool deleteId(int value) {
        bool deleted = false;
        root = remove(root, value, deleted);
        return deleted;
    }

    void inorderTraversal()   { inorder(root);   cout << endl; }
    void preorderTraversal()  { preorder(root);  cout << endl; }
    void postorderTraversal() { postorder(root); cout << endl; }

    int totalNodes() { return countNodes(root); }
    int treeHeight() { return height(root); }

    vector<int> toVector() {
        vector<int> v;
        collect(root, v);
        return v;
    }
};

/* ===================== HELPERS ===================== */

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

void showTree(BST& t) {
    cout << "  Current IDs (in-order): ";
    if (t.isEmpty()) cout << "(empty)" << endl;
    else t.inorderTraversal();
}

void doInsert(BST& t, int id) {
    if (t.insertId(id)) cout << "ID " << id << " inserted." << endl;
    else cout << "ID " << id << " already exists. Duplicate rejected, tree unchanged." << endl;
}

void doDelete(BST& t, int id) {
    if (t.isEmpty()) {
        cout << "Tree is empty. Nothing to delete." << endl;
        return;
    }
    if (t.deleteId(id)) {
        cout << "ID " << id << " deleted." << endl;
        showTree(t);
    } else {
        cout << "ID " << id << " does not exist. Nothing deleted." << endl;
    }
}

void doSearch(BST& t, int id) {
    if (t.isEmpty()) {
        cout << "Tree is empty. Nothing to search." << endl;
        return;
    }
    cout << "ID " << id << (t.searchId(id) ? " FOUND." : " NOT FOUND.") << endl;
}

/* Requirement 9: predict first, then run and compare.
   Change the sequence below to the one your instructor gives you and
   fill in the predicted values by hand BEFORE running. */
void predictionDemo() {
    cout << "\n===== PREDICTION vs ACTUAL DEMO =====" << endl;
    cout << "Start IDs : 55 35 75 25 45 65 85 40 50" << endl;
    cout << "Operations: insert 60, insert 20, delete 25, delete 35, delete 55" << endl;

    // ---- your hand-made predictions ----
    vector<int> predictedInorder = {20, 40, 45, 50, 60, 65, 75, 85};
    int predictedHeight = 4;
    cout << "Predicted in-order: 20 40 45 50 60 65 75 85 | height = 4" << endl;

    BST t;
    int start[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : start) t.insertId(id);

    t.insertId(60);
    t.insertId(20);
    t.deleteId(25);
    t.deleteId(35);
    t.deleteId(55);

    vector<int> actual = t.toVector();
    cout << "Actual in-order   : ";
    for (int x : actual) cout << x << " ";
    cout << "| height = " << t.treeHeight() << endl;

    bool match = (actual == predictedInorder) && (t.treeHeight() == predictedHeight);
    cout << (match ? "RESULT: prediction MATCHES the actual output."
                   : "RESULT: prediction does NOT match. Re-check your hand work.") << endl;
}

void repeatedDeletionDemo() {
    cout << "\n===== REPEATED DELETION OF THE SAME ID =====" << endl;
    BST t;
    int start[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : start) t.insertId(id);

    cout << "First  delete of 45:" << endl;
    doDelete(t, 45);
    cout << "Second delete of 45:" << endl;
    doDelete(t, 45);
    cout << "Behavior: the second attempt finds no node with 45, so deleteId returns\n"
            "false, the program prints a 'does not exist' message and the tree is\n"
            "left exactly as it was after the first deletion." << endl;
}

void printMenu() {
    cout << "\n========== Hospital & Emergency Inventory ==========" << endl;
    cout << "1. Insert an ID" << endl;
    cout << "2. Search for an ID" << endl;
    cout << "3. Delete an ID" << endl;
    cout << "4. Display in-order traversal" << endl;
    cout << "5. Display pre-order traversal" << endl;
    cout << "6. Display post-order traversal" << endl;
    cout << "7. Count the total number of nodes" << endl;
    cout << "8. Calculate the height of the BST" << endl;
    cout << "9. Exit" << endl;
}

/* ============================== MAIN ============================== */

int main() {
    predictionDemo();
    repeatedDeletionDemo();

    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) tree.insertId(id);

    cout << "\nInitial IDs loaded: 55 35 75 25 45 65 85 40 50" << endl;

    int choice;
    do {
        printMenu();
        choice = readInt("Enter your choice (1-9): ");

        switch (choice) {
        case 1:
            doInsert(tree, readInt("Enter ID to insert: "));
            break;
        case 2:
            doSearch(tree, readInt("Enter ID to search: "));
            break;
        case 3:
            doDelete(tree, readInt("Enter ID to delete: "));
            break;
        case 4:
            cout << "In-order  : ";
            if (tree.isEmpty()) cout << "Tree is empty." << endl; else tree.inorderTraversal();
            break;
        case 5:
            cout << "Pre-order : ";
            if (tree.isEmpty()) cout << "Tree is empty." << endl; else tree.preorderTraversal();
            break;
        case 6:
            cout << "Post-order: ";
            if (tree.isEmpty()) cout << "Tree is empty." << endl; else tree.postorderTraversal();
            break;
        case 7:
            cout << "Total number of nodes: " << tree.totalNodes() << endl;
            break;
        case 8:
            cout << "Height of the BST: " << tree.treeHeight() << endl;
            break;
        case 9:
            cout << "Exiting program. Memory is released by the destructor." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 9." << endl;
        }
    } while (choice != 9);

    return 0;
}