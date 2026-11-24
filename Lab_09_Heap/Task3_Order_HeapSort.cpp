#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

class OrderNode {
public:
    int orderId;
    string customer;
    int amount;
    OrderNode* left;
    OrderNode* right;
    OrderNode* parent;

    OrderNode(int id, string c, int a) {
        orderId = id;
        customer = c;
        amount = a;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class OrderMaxHeap {
private:
    OrderNode* root;
    int count;

    void swapData(OrderNode* a, OrderNode* b) {
        swap(a->orderId, b->orderId);
        swap(a->customer, b->customer);
        swap(a->amount, b->amount);
    }

    OrderNode* findInsertParent() {
        queue<OrderNode*> q;
        q.push(root);
        while (!q.empty()) {
            OrderNode* cur = q.front();
            q.pop();
            if (cur->left == NULL || cur->right == NULL)
                return cur;
            q.push(cur->left);
            q.push(cur->right);
        }
        return NULL;
    }

    OrderNode* findLastNode() {
        queue<OrderNode*> q;
        q.push(root);
        OrderNode* cur = NULL;
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            if (cur->left != NULL)  q.push(cur->left);
            if (cur->right != NULL) q.push(cur->right);
        }
        return cur;
    }

    void heapifyUp(OrderNode* node) {
        while (node->parent != NULL && node->amount > node->parent->amount) {
            cout << "   Heapify Up: " << node->amount << " swapped with parent "
                 << node->parent->amount << "\n";
            swapData(node, node->parent);
            node = node->parent;
        }
    }

    void heapifyDown(OrderNode* node) {
        while (node != NULL) {
            OrderNode* largest = node;
            if (node->left != NULL && node->left->amount > largest->amount)
                largest = node->left;
            if (node->right != NULL && node->right->amount > largest->amount)
                largest = node->right;
            if (largest == node) break;
            swapData(node, largest);
            node = largest;
        }
    }

public:
    OrderMaxHeap() { root = NULL; count = 0; }

    bool isEmpty() { return root == NULL; }
    int size() { return count; }

    void insert(int id, string customer, int amount) {
        OrderNode* node = new OrderNode(id, customer, amount);
        cout << "Insert order " << id << " (" << customer << ", Rs. " << amount << ")\n";
        if (root == NULL) {
            root = node;
        } else {
            OrderNode* p = findInsertParent();
            if (p->left == NULL) p->left = node;
            else p->right = node;
            node->parent = p;
            heapifyUp(node);
        }
        count++;
    }

    void deleteRoot(int& id, string& customer, int& amount) {
        id = root->orderId;
        customer = root->customer;
        amount = root->amount;
        OrderNode* last = findLastNode();
        if (last == root) {
            delete root;
            root = NULL;
            count--;
            return;
        }
        root->orderId = last->orderId;
        root->customer = last->customer;
        root->amount = last->amount;
        if (last->parent->right == last) last->parent->right = NULL;
        else last->parent->left = NULL;
        delete last;
        count--;
        heapifyDown(root);
    }

    void levelOrder() {
        if (root == NULL) { cout << "Heap is empty.\n"; return; }
        queue<OrderNode*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            cout << "  Level " << level << ": ";
            for (int i = 0; i < size; i++) {
                OrderNode* cur = q.front();
                q.pop();
                cout << cur->amount << "  ";
                if (cur->left != NULL)  q.push(cur->left);
                if (cur->right != NULL) q.push(cur->right);
            }
            cout << "\n";
            level++;
        }
    }
};

void line(string title) {
    cout << "\n==================================================\n";
    cout << "  " << title << "\n";
    cout << "==================================================\n";
}

int main() {
    cout << "Data Structure Lab 09 | BS Data Science\n";
    cout << "Task 3 - Online Shopping Order Sorting (Heap Sort)\n";

    OrderMaxHeap heap;

    line("1) Inserting 7 orders into Max Heap (Heapify Up)");
    heap.insert(1001, "Ali Raza",     4500);
    heap.insert(1002, "Sana Malik",   1200);
    heap.insert(1003, "Omer Farooq",  8900);
    heap.insert(1004, "Mehwish Ali",  2750);
    heap.insert(1005, "Junaid Akram", 6300);
    heap.insert(1006, "Rabia Saleem",  990);
    heap.insert(1007, "Danish Iqbal", 5150);

    cout << "\nMax Heap (Level Order) - order amounts:\n";
    heap.levelOrder();

    line("2) Heap Sort by repeated root deletion");
    const int MAX = 50;
    int n = heap.size();
    int deletedAmounts[MAX];
    int sortedAmounts[MAX];
    int sortedIds[MAX];
    string sortedNames[MAX];

    for (int i = 0; i < n; i++) {
        int id, amount;
        string customer;
        heap.deleteRoot(id, customer, amount);
        deletedAmounts[i] = amount;

        sortedAmounts[n - 1 - i] = amount;
        sortedIds[n - 1 - i] = id;
        sortedNames[n - 1 - i] = customer;
        cout << "Delete root " << setw(5) << amount << "  -> remaining heap: ";
        if (heap.isEmpty()) cout << "(empty)\n";
        else { cout << "\n"; heap.levelOrder(); }
    }

    line("3) Stored deleted amounts (deletion order)");
    cout << "  ";
    for (int i = 0; i < n; i++) cout << deletedAmounts[i] << "  ";
    cout << "\n";

    line("4) Order amounts in ascending order");
    cout << "  ";
    for (int i = 0; i < n; i++) cout << sortedAmounts[i] << "  ";
    cout << "\n\nSales report (lowest to highest):\n";
    cout << "  " << left << setw(6) << "No." << setw(10) << "Order ID"
         << setw(16) << "Customer" << "Amount (Rs.)\n";
    cout << "  ------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << "  " << left << setw(6) << i + 1 << setw(10) << sortedIds[i]
             << setw(16) << sortedNames[i] << sortedAmounts[i] << "\n";
    }

    return 0;
}