// Task 3: Game Player Turns using a Circular Singly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string playerName;
    Node* next;

    Node(string name) {
        playerName = name;
        next = NULL;
    }
};

class PlayerCircle {
private:
    Node* head;
    Node* tail;
    int count;

public:
    PlayerCircle() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void addPlayer(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            newNode->next = head;      // points to itself
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;         // last node connects back to first
        }
        count++;
    }

    // Each player's turn once
    void displayTurnsOnce() {
        cout << "Each player's turn (one round):" << endl;
        Node* temp = head;
        int turn = 1;
        do {
            cout << "  Turn " << turn++ << ": " << temp->playerName << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // Show that after the last player, it returns to the first
    void showCircularReturn() {
        cout << "Circular check:" << endl;
        cout << "  Last player  : " << tail->playerName << endl;
        cout << "  Next turn -> : " << tail->next->playerName
             << " (back to first player)" << endl;
    }

    ~PlayerCircle() {
        if (head == NULL) return;
        Node* temp = head->next;
        while (temp != head) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        delete head;
    }
};

int main() {
    PlayerCircle game;

    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Ahmed");
    game.addPlayer("Fatima");
    game.addPlayer("Usman");

    cout << "===== Game Player Turns (Circular Singly Linked List) =====" << endl << endl;
    game.displayTurnsOnce();
    cout << endl;
    game.showCircularReturn();

    return 0;
}
