// Task 2: Network Data Packet Management (Circular Queue)
#include <iostream>
using namespace std;

const int SIZE = 5;

class PacketQueue {
    int arr[SIZE];
    int front, rear, count;

public:
    PacketQueue() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isFull()  { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    void enqueue(int packet) {
        if (isFull()) {
            cout << "Buffer FULL! Packet " << packet << " dropped.\n";
            return;
        }
        rear = (rear + 1) % SIZE;      // circular movement
        arr[rear] = packet;
        count++;
        cout << "Packet " << packet << " stored at index " << rear << ".\n";
    }

    void transmit() {
        if (isEmpty()) {
            cout << "Buffer EMPTY! No packet to transmit.\n";
            return;
        }
        cout << "Packet " << arr[front] << " transmitted from index " << front << ".\n";
        front = (front + 1) % SIZE;    // circular movement
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }
        cout << "Packets waiting: ";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % SIZE;
            cout << arr[idx] << "[" << idx << "] ";
        }
        cout << endl;
    }
};

int main() {
    cout << "===== Network Data Packet Management =====\n\n";

    PacketQueue q;

    q.transmit();           // empty test
    cout << endl;

    q.enqueue(201);
    q.enqueue(202);
    q.enqueue(203);
    q.enqueue(204);
    q.enqueue(205);
    q.display();
    q.enqueue(206);         // full test
    cout << endl;

    q.transmit();           // 201 leaves, index 0 is free
    q.transmit();           // 202 leaves, index 1 is free
    q.display();
    cout << endl;

    q.enqueue(206);         // reuses index 0
    q.enqueue(207);         // reuses index 1
    q.display();

    return 0;
}
