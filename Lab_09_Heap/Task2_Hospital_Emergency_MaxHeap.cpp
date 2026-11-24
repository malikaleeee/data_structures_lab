#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

class PatientNode {
public:
    string name;
    string patientId;
    int priority;
    PatientNode* left;
    PatientNode* right;
    PatientNode* parent;

    PatientNode(string n, string id, int p) {
        name = n;
        patientId = id;
        priority = p;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class PatientMaxHeap {
private:
    PatientNode* root;
    int count;

    void swapData(PatientNode* a, PatientNode* b) {
        swap(a->name, b->name);
        swap(a->patientId, b->patientId);
        swap(a->priority, b->priority);
    }

    PatientNode* findInsertParent() {
        queue<PatientNode*> q;
        q.push(root);
        while (!q.empty()) {
            PatientNode* cur = q.front();
            q.pop();
            if (cur->left == NULL || cur->right == NULL)
                return cur;
            q.push(cur->left);
            q.push(cur->right);
        }
        return NULL;
    }

    PatientNode* findLastNode() {
        queue<PatientNode*> q;
        q.push(root);
        PatientNode* cur = NULL;
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur->left != NULL)  q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
        return cur;
    }

    void heapifyUp(PatientNode* node) {
        while (node->parent != NULL && node->priority > node->parent->priority) {
            cout << "   Heapify Up: " << node->name << " (P" << node->priority
                 << ") swapped with parent " << node->parent->name
                 << " (P" << node->parent->priority << ")\n";
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(PatientNode* node) {
        while (node != NULL) {
            PatientNode* largest = node;
            if (node->left != NULL && node->left->priority > largest->priority)
                largest = node->left;
            if (node->right != NULL && node->right->priority > largest->priority)
                largest = node->right;
            if (largest == node) break;
            cout << "   Heapify Down: " << node->name << " (P" << node->priority
                 << ") swapped with child " << largest->name
                 << " (P" << largest->priority << ")\n";
            swapData(node, largest);
            node = largest;
        }
    }

    void printTree(PatientNode* n, string indent, string label) {
        if (n == NULL) return;
        cout << indent << label << n->name << " (P" << n->priority << ")\n";
        printTree(n->left,  indent + "      ", "L---- ");
        printTree(n->right, indent + "      ", "R---- ");
    }

public:
    PatientMaxHeap() { root = NULL; count = 0; }

    void insert(string name, string id, int priority) {
        PatientNode* node = new PatientNode(name, id, priority);
        cout << "Admit " << name << " (" << id << ", priority " << priority << ")\n";
        if (root == NULL) {
            root = node;
        } else {
            PatientNode* p = findInsertParent();
            if (p->left == NULL) p->left = node;
            else p->right = node;
            node->parent = p;
            heapifyUp(node);
        }
        count++;
    }

    void showHighest() {
        if (root == NULL) { cout << "No patients waiting.\n"; return; }
        cout << "Highest priority patient: " << root->name << " (" << root->patientId
             << ", priority " << root->priority << ")\n";
    }

    void treatPatient() {
        if (root == NULL) { cout << "No patients waiting.\n"; return; }
        cout << "Treated and removed: " << root->name << " (" << root->patientId
             << ", priority " << root->priority << ")\n";
        PatientNode* last = findLastNode();
        if (last == root) {
            delete root;
            root = NULL;
            count--;
            return;
        }
        cout << "   Last node " << last->name << " (P" << last->priority
             << ") moved to the root\n";
        root->name = last->name;
        root->patientId = last->patientId;
        root->priority = last->priority;
        if (last->parent->right == last) last->parent->right = NULL;
        else last->parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void levelOrder() {
        if (root == NULL) { cout << "No patients waiting.\n"; return; }
        cout << "  " << left << setw(8) << "Level" << setw(18) << "Patient"
             << setw(10) << "ID" << "Priority\n";
        cout << "  ------------------------------------------\n";
        queue<PatientNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                PatientNode* cur = q.front();
                q.pop();
                cout << "  " << left << setw(8) << level << setw(18) << cur->name
                     << setw(10) << cur->patientId << cur->priority << "\n";
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
    cout << "Task 2 - Hospital Emergency Management System (Max Heap)\n";

    PatientMaxHeap heap;

    line("1) Admitting 7 patients (Heapify Up after each)");
    heap.insert("Ahmed Raza",     "P-201", 4);
    heap.insert("Zainab Bibi",    "P-202", 7);
    heap.insert("Imran Shah",     "P-203", 9);
    heap.insert("Nadia Khan",     "P-204", 3);
    heap.insert("Kashif Mehmood", "P-205", 8);
    heap.insert("Hira Iqbal",     "P-206", 10);
    heap.insert("Tahir Abbas",    "P-207", 6);

    line("2) All patients - Level Order Traversal");
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();

    line("3) Patient with highest priority");
    heap.showHighest();

    line("4) Treat the patient and delete from heap");
    heap.treatPatient();

    line("5) After Heapify Down - next patient to treat");
    heap.showHighest();
    cout << "\nUpdated heap (Level Order):\n";
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();
    cout << "\nPatients still waiting: " << heap.size() << "\n";

    return 0;
}
