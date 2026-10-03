// Task 2: Image Gallery using a Doubly Linked List
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string imageName;
    Node* prev;
    Node* next;

    Node(string name) {
        imageName = name;
        prev = NULL;
        next = NULL;
    }
};

class ImageGallery {
private:
    Node* head;
    Node* tail;

public:
    ImageGallery() {
        head = NULL;
        tail = NULL;
    }

    void addImage(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // First -> Last using next pointer
    void displayForward() {
        cout << "Images (First -> Last) using 'next':" << endl;
        Node* temp = head;
        while (temp != NULL) {
            cout << "  " << temp->imageName << endl;
            temp = temp->next;
        }
    }

    // Last -> First using prev pointer
    void displayBackward() {
        cout << "Images (Last -> First) using 'prev':" << endl;
        Node* temp = tail;
        while (temp != NULL) {
            cout << "  " << temp->imageName << endl;
            temp = temp->prev;
        }
    }

    // Demonstrate moving both directions like a gallery viewer
    void demonstrateNavigation() {
        cout << "Navigation Demo (Next / Previous buttons):" << endl;
        Node* current = head;
        cout << "  Viewing    : " << current->imageName << endl;

        current = current->next;
        cout << "  Next  >>   : " << current->imageName << endl;

        current = current->next;
        cout << "  Next  >>   : " << current->imageName << endl;

        current = current->prev;
        cout << "  << Prev    : " << current->imageName << endl;

        current = current->next->next->next;
        cout << "  Next x3 >> : " << current->imageName << " (last image)" << endl;

        current = current->prev;
        cout << "  << Prev    : " << current->imageName << endl;
    }

    ~ImageGallery() {
        Node* temp = head;
        while (temp != NULL) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    ImageGallery gallery;

    gallery.addImage("sunset.jpg");
    gallery.addImage("mountains.png");
    gallery.addImage("beach.jpg");
    gallery.addImage("city_night.png");
    gallery.addImage("forest.jpg");

    cout << "===== Image Gallery (Doubly Linked List) =====" << endl << endl;
    gallery.displayForward();
    cout << endl;
    gallery.displayBackward();
    cout << endl;
    gallery.demonstrateNavigation();

    return 0;
}
