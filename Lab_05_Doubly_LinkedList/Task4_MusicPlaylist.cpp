// Task 4: Music Playlist using a Circular Singly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string songName;
    Node* next;

    Node(string name) {
        songName = name;
        next = NULL;
    }
};

class Playlist {
private:
    Node* head;
    Node* tail;
    int count;

public:
    Playlist() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void addSong(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            newNode->next = head;      // circular from the start
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;         // last song links to first song, NOT NULL
        }
        count++;
    }

    // Display all songs once
    void displayOnce() {
        cout << "Playlist (all songs once):" << endl;
        Node* temp = head;
        int i = 1;
        do {
            cout << "  " << i++ << ". " << temp->songName << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // Keep following next pointers; the circle brings us back automatically
    void playRounds(int rounds) {
        cout << "Playing playlist for " << rounds << " complete rounds:" << endl;
        Node* current = head;
        int totalPlays = rounds * count;
        for (int i = 0; i < totalPlays; i++) {
            if (i % count == 0) {
                cout << "  --- Round " << (i / count) + 1 << " ---" << endl;
            }
            cout << "  Now playing: " << current->songName << endl;
            current = current->next;   // after last song, goes to first song
        }
    }

    ~Playlist() {
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
    Playlist playlist;

    playlist.addSong("Song A - Morning Light");
    playlist.addSong("Song B - City Lights");
    playlist.addSong("Song C - Ocean Waves");
    playlist.addSong("Song D - Night Drive");
    playlist.addSong("Song E - Rainy Day");

    cout << "===== Music Playlist (Circular Singly Linked List) =====" << endl << endl;
    playlist.displayOnce();
    cout << endl;
    playlist.playRounds(2);

    return 0;
}
