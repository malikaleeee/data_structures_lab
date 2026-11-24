#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;
    Node(int value) { data = value; left = NULL; right = NULL; }
};

class MaxHeap
{
public:
    Node* root;
    MaxHeap() { root = NULL; }

    // Insert at next free spot (level order), then heapify up
    void insert(int value)
    {
        Node* newNode = new Node(value);
        if (root == NULL) { root = newNode; return; }

        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* temp = q.front(); q.pop();
            if (temp->left == NULL) { temp->left = newNode; break; }
            else q.push(temp->left);
            if (temp->right == NULL) { temp->right = newNode; break; }
            else q.push(temp->right);
        }
        heapifyUp(newNode);
    }

    void heapifyUp(Node* newNode)
    {
        Node* parent = NULL;
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* temp = q.front(); q.pop();
            if (temp->left == newNode || temp->right == newNode)
            {
                parent = temp;
                break;
            }
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
        if (parent != NULL && newNode->data > parent->data)
        {
            swap(newNode->data, parent->data);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Node* temp)
    {
        Node* largest = temp;
        if (temp->left != NULL && temp->left->data > largest->data)
            largest = temp->left;
        if (temp->right != NULL && temp->right->data > largest->data)
            largest = temp->right;
        if (largest != temp)
        {
            swap(temp->data, largest->data);
            heapifyDown(largest);
        }
    }

    // Removes root, returns the removed (largest) value
    int deleteRoot()
    {
        int value = root->data;
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return value;
        }

        queue<Node*> q;
        q.push(root);
        Node* last = root;
        Node* parent = NULL;
        while (!q.empty())
        {
            Node* temp = q.front(); q.pop();
            if (temp->left != NULL)
            {
                parent = temp; last = temp->left; q.push(temp->left);
            }
            if (temp->right != NULL)
            {
                parent = temp; last = temp->right; q.push(temp->right);
            }
        }
        root->data = last->data;
        if (parent->right == last) parent->right = NULL;
        else parent->left = NULL;
        delete last;

        heapifyDown(root);
        return value;
    }

    void display()
    {
        if (root == NULL) { cout << "Heap is empty!"; return; }
        queue<Node*> q;
        q.push(root);
        while (!q.empty())
        {
            Node* temp = q.front(); q.pop();
            cout << temp->data << " ";
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
    }

    // Empties the heap; prints ascending and descending
    void heapSort()
    {
        int sorted[100];
        int count = 0;
        while (root != NULL)
            sorted[count++] = deleteRoot();   // largest -> smallest

        cout << "Descending Order: ";
        for (int i = 0; i < count; i++) cout << sorted[i] << " ";

        cout << "\nAscending Order: ";
        for (int i = count - 1; i >= 0; i--) cout << sorted[i] << " ";
        cout << endl;
    }
};

int main()
{
    // Task 1 + 2: build, display, delete root
    MaxHeap h;
    h.insert(50); h.insert(30); h.insert(40); h.insert(10); h.insert(20);

    cout << "Level Order (Max Heap): ";
    h.display();

    h.deleteRoot();
    cout << "\nAfter Deletion: ";
    h.display();

    // Task 3: heap sort
    MaxHeap s;
    s.insert(40); s.insert(20); s.insert(50); s.insert(10); s.insert(30);
    cout << "\n\nHeap Sort:\n";
    s.heapSort();

    return 0;
}