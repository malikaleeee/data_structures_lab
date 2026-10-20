// Task 1: Bank Customer Service System (Simple Linear Queue)
#include <iostream>
using namespace std;

const int SIZE = 5;

class BankQueue {
    int arr[SIZE];
    int front, rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    bool isFull()  { return rear == SIZE - 1; }
    bool isEmpty() { return front == -1 || front > rear; }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Overflow! Queue is full. Customer " << token << " cannot join.\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = token;
        cout << "Customer " << token << " joined the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow! No customers waiting.\n";
            return;
        }
        cout << "Customer " << arr[front] << " is being served.\n";
        front++;
    }

    void display() {
        if (isEmpty()) {
            cout << "No customers waiting.\n";
            return;
        }
        cout << "Waiting customers: ";
        for (int i = front; i <= rear; i++) cout << arr[i] << " ";
        cout << endl;
    }

    int count() {
        if (isEmpty()) return 0;
        return rear - front + 1;
    }
};

int main() {
    cout << "===== Bank Customer Service System =====\n\n";

    BankQueue q;

    q.dequeue();            // underflow test
    cout << endl;

    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);
    q.display();
    cout << "Number of waiting customers: " << q.count() << "\n\n";

    q.dequeue();            // 101 served first
    q.display();
    cout << "Number of waiting customers: " << q.count() << "\n\n";

    q.enqueue(104);
    q.enqueue(105);
    q.enqueue(106);         // overflow (linear queue does not reuse space)
    q.display();
    cout << "Number of waiting customers: " << q.count() << endl;

    return 0;
}
