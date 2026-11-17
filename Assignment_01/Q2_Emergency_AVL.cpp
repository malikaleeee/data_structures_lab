// ============================================================
//  Data Structure Lab - BSDS-III (Evening) - Lab 08 (Trees)
//  Name    : Anees Ahmad
//  Roll No : 2502491
//  Program : BS Data Science
//  Q2      : Emergency Rescue Operations - AVL Tree
// ============================================================
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

// ---------- Node class: one emergency request ----------
class Node {
public:
    int id;             // emergency ID (key)
    string location;
    int severity;       // 1 (low) ... 10 (critical)
    int height;         // leaf = 1
    Node* left;
    Node* right;

    Node(int i, string loc, int sev) {
        id = i;
        location = loc;
        severity = sev;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

// ---------- AVL Tree class ----------
class EmergencyAVL {
private:
    Node* root;

    int height(Node* n) { return (n == NULL) ? 0 : n->height; }

    int maxOf(int a, int b) { return (a > b) ? a : b; }

    void updateHeight(Node* n) {
        n->height = 1 + maxOf(height(n->left), height(n->right));
    }

    // Balance Factor = height(left) - height(right)
    int balanceFactor(Node* n) {
        if (n == NULL) return 0;
        return height(n->left) - height(n->right);
    }

    /*  Right Rotation:
            y                x
          / \             /   \
         x   T3   -->    T1    y
        / \                   / \
       T1  T2                T2  T3
    */
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    /*  Left Rotation:
          x                    y
        / \                 /   \
       T1  y      -->      x     T3
          / \             / \
         T2  T3          T1  T2
    */
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // checks balance of node n and applies the right rotation case
    Node* balance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1 && balanceFactor(n->left) >= 0) {          // LL
            cout << "   -> LL case at " << n->id << " : Right Rotation\n";
            return rightRotate(n);
        }
        if (bf > 1 && balanceFactor(n->left) < 0) {           // LR
            cout << "   -> LR case at " << n->id
                 << " : Left Rotation on " << n->left->id << ", then Right Rotation\n";
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }
        if (bf < -1 && balanceFactor(n->right) <= 0) {        // RR
            cout << "   -> RR case at " << n->id << " : Left Rotation\n";
            return leftRotate(n);
        }
        if (bf < -1 && balanceFactor(n->right) > 0) {         // RL
            cout << "   -> RL case at " << n->id
                 << " : Right Rotation on " << n->right->id << ", then Left Rotation\n";
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }
        return n;                                             // already balanced
    }

    Node* insert(Node* n, int id, string loc, int sev) {
        if (n == NULL) return new Node(id, loc, sev);
        if (id < n->id)
            n->left = insert(n->left, id, loc, sev);
        else if (id > n->id)
            n->right = insert(n->right, id, loc, sev);
        else {
            cout << "   Emergency ID " << id << " already exists!\n";
            return n;
        }
        return balance(n);                    // rebalance on the way back up
    }

    Node* minNode(Node* n) {
        while (n->left != NULL) n = n->left;
        return n;
    }

    Node* remove(Node* n, int id) {
        if (n == NULL) {
            cout << "   Emergency ID " << id << " not found.\n";
            return NULL;
        }
        if (id < n->id)
            n->left = remove(n->left, id);
        else if (id > n->id)
            n->right = remove(n->right, id);
        else {
            if (n->left == NULL || n->right == NULL) {   // 0 or 1 child
                Node* temp = (n->left != NULL) ? n->left : n->right;
                delete n;
                return temp;
            }
            // 2 children: copy in-order successor, then delete it
            Node* succ = minNode(n->right);
            cout << "   (two children: replaced by successor " << succ->id << ")\n";
            n->id = succ->id;
            n->location = succ->location;
            n->severity = succ->severity;
            n->right = remove(n->right, succ->id);
        }
        return balance(n);                    // rebalance on the way back up
    }

    string level(int s) {
        if (s >= 9) return "Critical";
        if (s >= 7) return "High";
        if (s >= 4) return "Medium";
        return "Low";
    }

    void printRecord(Node* n) {
        cout << "  " << left << setw(6) << n->id << setw(18) << n->location
             << n->severity << " (" << level(n->severity) << ")\n";
    }

    void inorder(Node* n) {
        if (n == NULL) return;
        inorder(n->left);
        printRecord(n);
        inorder(n->right);
    }

    void heightAndBF(Node* n) {
        if (n == NULL) return;
        heightAndBF(n->left);
        cout << "  " << left << setw(6) << n->id << setw(10) << n->height
             << balanceFactor(n) << "\n";
        heightAndBF(n->right);
    }

    void printTree(Node* n, string indent, string label) {
        if (n == NULL) return;
        cout << indent << label << n->id << " [h=" << n->height
             << ", bf=" << balanceFactor(n) << "]\n";
        printTree(n->left,  indent + "      ", "L---- ");
        printTree(n->right, indent + "      ", "R---- ");
    }

public:
    EmergencyAVL() { root = NULL; }

    void insert(int id, string loc, int sev) {
        cout << "Insert " << id << " (" << loc << ")\n";
        root = insert(root, id, loc, sev);
    }

    void remove(int id) {
        cout << "Delete " << id << "\n";
        root = remove(root, id);
    }

    void search(int id) {
        Node* cur = root;
        int steps = 0;
        while (cur != NULL) {
            steps++;
            if (id == cur->id) {
                cout << "Emergency " << id << " FOUND after " << steps << " comparisons -> "
                     << cur->location << ", severity " << cur->severity
                     << " (" << level(cur->severity) << ")\n";
                return;
            }
            cur = (id < cur->id) ? cur->left : cur->right;
        }
        cout << "Emergency " << id << " NOT FOUND.\n";
    }

    void header() {
        cout << "  " << left << setw(6) << "ID" << setw(18) << "Location" << "Severity\n";
        cout << "  ------------------------------------\n";
    }

    void inorder() { header(); inorder(root); }

    void levelOrder() {                       // BFS using a queue
        if (root == NULL) { cout << "Tree is empty.\n"; return; }
        queue<Node*> q;
        q.push(root);
        int lvl = 0;
        while (!q.empty()) {
            int size = q.size();
            cout << "  Level " << lvl << ": ";
            for (int i = 0; i < size; i++) {
                Node* cur = q.front();
                q.pop();
                cout << cur->id << "(" << cur->location << ")  ";
                if (cur->left != NULL)  q.push(cur->left);
                if (cur->right != NULL) q.push(cur->right);
            }
            cout << "\n";
            lvl++;
        }
    }

    void heightAndBF() {
        cout << "  " << left << setw(6) << "ID" << setw(10) << "Height" << "Balance Factor\n";
        cout << "  ----------------------------\n";
        heightAndBF(root);
    }

    int treeHeight() { return height(root); }

    void printTree() { printTree(root, "", "Root: "); }
};

void line(string title) {
    cout << "\n==================================================\n";
    cout << "  " << title << "\n";
    cout << "==================================================\n";
}

int main() {
    cout << "Name: Anees Ahmad | Roll No: 2502491 | BS Data Science\n";
    cout << "Q2 - Emergency Rescue Operations (AVL Tree)\n";

    EmergencyAVL avl;

    line("1) Inserting 14 emergency records (auto-balancing)");
    avl.insert(50, "Islamabad",   7);
    avl.insert(40, "Rawalpindi",  5);
    avl.insert(30, "Murree",      9);   // LL
    avl.insert(60, "Lahore",      4);
    avl.insert(70, "Karachi",     8);   // RR
    avl.insert(65, "Quetta",      6);   // RR
    avl.insert(35, "Peshawar",   10);
    avl.insert(33, "Abbottabad",  3);   // RL
    avl.insert(45, "Multan",      5);
    avl.insert(47, "Swat",        9);   // LR
    avl.insert(80, "Gilgit",      8);
    avl.insert(20, "Faisalabad",  2);   // LL
    avl.insert(90, "Hyderabad",   6);
    avl.insert(25, "Sialkot",     7);   // LR

    cout << "\nAVL Tree after all insertions:\n";
    avl.printTree();

    line("2) Height and Balance Factor of each node");
    avl.heightAndBF();
    cout << "Tree height = " << avl.treeHeight() << "\n";

    line("3) Searching by Emergency ID");
    avl.search(47);
    avl.search(90);
    avl.search(55);

    line("4) Traversals");
    cout << "In-order (records sorted by Emergency ID):\n";
    avl.inorder();
    cout << "\nLevel-order (BFS):\n";
    avl.levelOrder();

    line("5) Deleting emergency records (auto-balancing)");
    avl.remove(35);
    avl.remove(65);
    avl.remove(40);

    line("6) Final balanced AVL Tree");
    avl.printTree();
    cout << "\nHeight and Balance Factor:\n";
    avl.heightAndBF();
    cout << "\nAll emergency records by Emergency ID:\n";
    avl.inorder();
    cout << "\nLevel-order (BFS):\n";
    avl.levelOrder();

    return 0;
}
