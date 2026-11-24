#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

class MedicineNode {
public:
    string name;
    string medicineId;
    int expiry;
    MedicineNode* left;
    MedicineNode* right;
    MedicineNode* parent;

    MedicineNode(string n, string id, int e) {
        name = n;
        medicineId = id;
        expiry = e;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

string showDate(int d) {
    string s = to_string(d);
    return s.substr(0, 4) + "-" + s.substr(4, 2) + "-" + s.substr(6, 2);
}

class MedicineMinHeap {
private:
    MedicineNode* root;
    int count;

    void swapData(MedicineNode* a, MedicineNode* b) {
        swap(a->name, b->name);
        swap(a->medicineId, b->medicineId);
        swap(a->expiry, b->expiry);
    }

    MedicineNode* findInsertParent() {
        queue<MedicineNode*> q;
        q.push(root);
        while (!q.empty()) {
            MedicineNode* cur = q.front();
            q.pop();
            if (cur->left == NULL || cur->right == NULL)
                return cur;
            q.push(cur->left);
            q.push(cur->right);
        }
        return NULL;
    }

    MedicineNode* findLastNode() {
        queue<MedicineNode*> q;
        q.push(root);
        MedicineNode* cur = NULL;
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur->left != NULL)  q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
        return cur;
    }

    void heapifyUp(MedicineNode* node) {
        while (node->parent != NULL && node->expiry < node->parent->expiry) {
            cout << "   Heapify Up: " << node->name << " (" << node->expiry
                 << ") swapped with parent " << node->parent->name
                 << " (" << node->parent->expiry << ")\n";
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(MedicineNode* node) {
        while (node != NULL) {
            MedicineNode* smallest = node;
            if (node->left != NULL && node->left->expiry < smallest->expiry)
                smallest = node->left;
            if (node->right != NULL && node->right->expiry < smallest->expiry)
                smallest = node->right;
            if (smallest == node) break;
            cout << "   Heapify Down: " << node->name << " (" << node->expiry
                 << ") swapped with child " << smallest->name
                 << " (" << smallest->expiry << ")\n";
            swapData(node, smallest);
            node = smallest;
        }
    }

    void printTree(MedicineNode* n, string indent, string label) {
        if (n == NULL) return;
        cout << indent << label << n->name << " (" << n->expiry << ")\n";
        printTree(n->left,  indent + "      ", "L---- ");
        printTree(n->right, indent + "      ", "R---- ");
    }

public:
    MedicineMinHeap() { root = NULL; count = 0; }

    void insert(string name, string id, int expiry) {
        MedicineNode* node = new MedicineNode(name, id, expiry);
        cout << "Insert " << name << " (" << id << ", expiry " << expiry << ")\n";
        if (root == NULL) {
            root = node;
        } else {
            MedicineNode* p = findInsertParent();
            if (p->left == NULL) p->left = node;
            else p->right = node;
            node->parent = p;
            heapifyUp(node);
        }
        count++;
    }

    void showNearest() {
        if (root == NULL) { cout << "No medicines in store.\n"; return; }
        cout << "Nearest expiry: " << root->name << " (" << root->medicineId
             << ", expires " << showDate(root->expiry) << ")\n";
    }

    void deleteMin() {
        if (root == NULL) { cout << "No medicines in store.\n"; return; }
        cout << "Checked and removed: " << root->name << " (" << root->medicineId
             << ", expiry " << root->expiry << ")\n";
        MedicineNode* last = findLastNode();
        if (last == root) {
            delete root;
            root = NULL;
            count--;
            return;
        }
        cout << "   Last node " << last->name << " (" << last->expiry << ") moved to the root\n";
        root->name = last->name;
        root->medicineId = last->medicineId;
        root->expiry = last->expiry;
        if (last->parent->right == last) last->parent->right = NULL;
        else last->parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void levelOrder() {
        if (root == NULL) { cout << "No medicines in store.\n"; return; }
        cout << "  " << left << setw(8) << "Level" << setw(14) << "Medicine"
             << setw(10) << "ID" << setw(12) << "Expiry" << "Date\n";
        cout << "  -----------------------------------------------------\n";
        queue<MedicineNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                MedicineNode* cur = q.front();
                q.pop();
                cout << "  " << left << setw(8) << level << setw(14) << cur->name
                     << setw(10) << cur->medicineId << setw(12) << cur->expiry
                     << showDate(cur->expiry) << "\n";
                if (cur->left != NULL)  q.push(cur->left);
                if (cur->right != NULL) q.push(cur->right);
            }
            level++;
        }
    }

    void printTree() { printTree(root, "", "Root: "); }
    int size() { return count; }
};

void line(string title) {
    cout << "\n==================================================\n";
    cout << "  " << title << "\n";
    cout << "==================================================\n";
}

int main() {
    cout << "Data Structure Lab 09 | BS Data Science\n";
    cout << "Task 4 - Hospital Medicine Expiry Management (Min Heap)\n";

    MedicineMinHeap heap;

    line("1) Inserting 7 medicines (Heapify Up after each)");
    heap.insert("Panadol",   "MED-01", 20270315);
    heap.insert("Augmentin", "MED-02", 20261210);
    heap.insert("Brufen",    "MED-03", 20270120);
    heap.insert("Insulin",   "MED-04", 20261201);
    heap.insert("Ventolin",  "MED-05", 20280530);
    heap.insert("Flagyl",    "MED-06", 20261225);
    heap.insert("Amoxil",    "MED-07", 20270801);

    line("2) Min Heap - Level Order Traversal");
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();

    line("3) Medicine with nearest expiry date");
    heap.showNearest();

    line("4) Delete the nearest-expiry medicine");
    heap.deleteMin();

    line("5) Updated Min Heap after Heapify Down");
    heap.showNearest();
    cout << "\n";
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();
    cout << "\nMedicines left in store: " << heap.size() << "\n";

    return 0;
}