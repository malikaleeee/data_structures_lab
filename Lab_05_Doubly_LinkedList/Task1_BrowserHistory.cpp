// Task 1: Browser History using a Doubly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string website;
    Node* prev;
    Node* next;

    Node(string name) {
        website = name;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;

public:
    BrowserHistory() {
        head = NULL;
        tail = NULL;
    }

    // Add a website at the end (most recent visit)
    void visit(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // First visited -> last visited (uses next)
    void displayForward() {
        cout << "History (First Visited -> Last Visited):" << endl;
        Node* temp = head;
        int i = 1;
        while (temp != NULL) {
            cout << "  " << i++ << ". " << temp->website << endl;
            temp = temp->next;
        }
    }

    // Last visited -> first visited (uses prev)
    void displayReverse() {
        cout << "History (Last Visited -> First Visited):" << endl;
        Node* temp = tail;
        int i = 1;
        while (temp != NULL) {
            cout << "  " << i++ << ". " << temp->website << endl;
            temp = temp->prev;
        }
    }

    ~BrowserHistory() {
        Node* temp = head;
        while (temp != NULL) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    BrowserHistory history;

    history.visit("www.google.com");
    history.visit("www.youtube.com");
    history.visit("www.github.com");
    history.visit("www.stackoverflow.com");
    history.visit("www.wikipedia.org");

    cout << "===== Browser History (Doubly Linked List) =====" << endl << endl;
    history.displayForward();
    cout << endl;
    history.displayReverse();

    return 0;
}
