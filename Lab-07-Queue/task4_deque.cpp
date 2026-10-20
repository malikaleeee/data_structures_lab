// Task 4: Train Station Passenger Management (Deque using circular array)
#include <iostream>
using namespace std;

const int SIZE = 5;

class PassengerDeque {
    int arr[SIZE];
    int front, rear, count;

public:
    PassengerDeque() {
        front = 0;
        rear = SIZE - 1;
        count = 0;
    }

    bool isFull()  { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    void insertFront(int id) {
        if (isFull()) { cout << "Deque FULL! Cannot add " << id << " at front.\n"; return; }
        front = (front - 1 + SIZE) % SIZE;
        arr[front] = id;
        count++;
        cout << "Request " << id << " added at FRONT.\n";
    }

    void insertRear(int id) {
        if (isFull()) { cout << "Deque FULL! Cannot add " << id << " at rear.\n"; return; }
        rear = (rear + 1) % SIZE;
        arr[rear] = id;
        count++;
        cout << "Request " << id << " added at REAR.\n";
    }

    void deleteFront() {
        if (isEmpty()) { cout << "Deque EMPTY! Nothing to remove from front.\n"; return; }
        cout << "Request " << arr[front] << " removed from FRONT.\n";
        front = (front + 1) % SIZE;
        count--;
    }

    void deleteRear() {
        if (isEmpty()) { cout << "Deque EMPTY! Nothing to remove from rear.\n"; return; }
        cout << "Request " << arr[rear] << " removed from REAR.\n";
        rear = (rear - 1 + SIZE) % SIZE;
        count--;
    }

    void display() {
        if (isEmpty()) { cout << "Deque is empty.\n"; return; }
        cout << "Front -> ";
        for (int i = 0; i < count; i++) {
            cout << arr[(front + i) % SIZE];
            if (i < count - 1) cout << ", ";
        }
        cout << " <- Rear\n";
    }
};

int main() {
    cout << "===== Train Station Passenger Management =====\n\n";

    PassengerDeque d;

    d.deleteFront();        // empty test
    d.deleteRear();
    cout << endl;

    d.insertRear(301);
    d.insertRear(302);
    d.insertFront(300);
    d.display();            // Front -> 300, 301, 302 <- Rear
    cout << endl;

    d.insertFront(299);
    d.insertRear(303);
    d.display();
    d.insertRear(304);      // full test
    cout << endl;

    d.deleteFront();
    d.deleteRear();
    d.display();

    return 0;
}
