#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

class StudentNode {
public:
    string name;
    int rollNo;
    int marks;
    StudentNode* left;
    StudentNode* right;
    StudentNode* parent;

    StudentNode(string n, int r, int m) {
        name = n;
        rollNo = r;
        marks = m;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class StudentMaxHeap {
private:
    StudentNode* root;
    int count;

    void swapData(StudentNode* a, StudentNode* b) {
        swap(a->name, b->name);
        swap(a->rollNo, b->rollNo);
        swap(a->marks, b->marks);
    }

    StudentNode* findInsertParent() {
        queue<StudentNode*> q;
        q.push(root);
        while (!q.empty()) {
            StudentNode* cur = q.front();
            q.pop();
            if (cur->left == NULL || cur->right == NULL)
                return cur;
            q.push(cur->left);
            q.push(cur->right);
        }
        return NULL;
    }

    StudentNode* findLastNode() {
        queue<StudentNode*> q;
        q.push(root);
        StudentNode* cur = NULL;
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur->left != NULL)  q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
        return cur;
    }

    void heapifyUp(StudentNode* node) {
        while (node->parent != NULL && node->marks > node->parent->marks) {
            cout << "   Heapify Up: " << node->name << " (" << node->marks
                 << ") swapped with parent " << node->parent->name
                 << " (" << node->parent->marks << ")\n";
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(StudentNode* node) {
        while (node != NULL) {
            StudentNode* largest = node;
            if (node->left != NULL && node->left->marks > largest->marks)
                largest = node->left;
            if (node->right != NULL && node->right->marks > largest->marks)
                largest = node->right;
            if (largest == node) break;
            cout << "   Heapify Down: " << node->name << " (" << node->marks
                 << ") swapped with child " << largest->name
                 << " (" << largest->marks << ")\n";
            swapData(node, largest);
            node = largest;
        }
    }

    void printTree(StudentNode* n, string indent, string label) {
        if (n == NULL) return;
        cout << indent << label << n->name << " (" << n->marks << ")\n";
        printTree(n->left,  indent + "      ", "L---- ");
        printTree(n->right, indent + "      ", "R---- ");
    }

public:
    StudentMaxHeap() { root = NULL; count = 0; }

    void insert(string name, int roll, int marks) {
        StudentNode* node = new StudentNode(name, roll, marks);
        cout << "Insert " << name << " (marks " << marks << ")\n";
        if (root == NULL) {
            root = node;
        } else {
            StudentNode* p = findInsertParent();
            if (p->left == NULL) p->left = node;
            else p->right = node;
            node->parent = p;
            heapifyUp(node);
        }
        count++;
    }

    void deleteMax() {
        if (root == NULL) { cout << "Heap is empty.\n"; return; }
        cout << "Deleting top student: " << root->name << " (Roll " << root->rollNo
             << ", marks " << root->marks << ")\n";
        StudentNode* last = findLastNode();
        if (last == root) {
            delete root;
            root = NULL;
            count--;
            return;
        }
        cout << "   Last node " << last->name << " (" << last->marks << ") moved to the root\n";
        root->name = last->name;
        root->rollNo = last->rollNo;
        root->marks = last->marks;
        if (last->parent->right == last) last->parent->right = NULL;
        else last->parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void levelOrder() {
        if (root == NULL) { cout << "Heap is empty.\n"; return; }
        cout << "  " << left << setw(8) << "Level" << setw(16) << "Name"
             << setw(10) << "Roll No" << "Marks\n";
        cout << "  ----------------------------------------\n";
        queue<StudentNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                StudentNode* cur = q.front();
                q.pop();
                cout << "  " << left << setw(8) << level << setw(16) << cur->name
                     << setw(10) << cur->rollNo << cur->marks << "\n";
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
    cout << "Task 1 - University Student Merit Ranking (Max Heap)\n";

    StudentMaxHeap heap;

    line("1) Inserting 7 students (Heapify Up after each)");
    heap.insert("Ali Khan",     101, 78);
    heap.insert("Sara Ahmed",   102, 85);
    heap.insert("Usman Tariq",  103, 92);
    heap.insert("Ayesha Noor",  104, 67);
    heap.insert("Hamza Ali",    105, 88);
    heap.insert("Fatima Zahra", 106, 95);
    heap.insert("Bilal Hassan", 107, 73);

    line("2) Max Heap - Level Order Traversal");
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();

    line("3) Delete student with highest marks");
    heap.deleteMax();

    line("4) Updated Max Heap after Heapify Down");
    heap.levelOrder();
    cout << "\nHeap as a tree:\n";
    heap.printTree();
    cout << "\nTotal students in heap: " << heap.size() << "\n";

    return 0;
}