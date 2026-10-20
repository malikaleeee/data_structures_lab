// Task 3: Hospital Emergency Department (Priority Queue using array)
// Priority rule: a SMALLER number means HIGHER urgency (1 = most urgent).
// If two patients have the same priority, the one who arrived first is treated first.
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Patient {
    string id;
    int priority;
};

class EmergencyQueue {
    Patient arr[SIZE];
    int count;

public:
    EmergencyQueue() { count = 0; }

    bool isFull()  { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    // Insert in sorted order so the most urgent patient is always at index 0
    void addPatient(string id, int priority) {
        if (isFull()) {
            cout << "Queue full! Cannot admit " << id << ".\n";
            return;
        }
        int i = count - 1;
        while (i >= 0 && arr[i].priority > priority) {
            arr[i + 1] = arr[i];   // shift less urgent patients back
            i--;
        }
        arr[i + 1].id = id;
        arr[i + 1].priority = priority;
        count++;
        cout << "Patient " << id << " admitted with priority " << priority << ".\n";
    }

    void treatPatient() {
        if (isEmpty()) {
            cout << "No patients waiting. Queue is empty.\n";
            return;
        }
        cout << "Treating patient " << arr[0].id
             << " (priority " << arr[0].priority << ").\n";
        for (int i = 0; i < count - 1; i++) arr[i] = arr[i + 1];
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting patients:\n";
        for (int i = 0; i < count; i++)
            cout << "  " << arr[i].id << "  -> Priority " << arr[i].priority << endl;
    }
};

int main() {
    cout << "===== Hospital Emergency Department =====\n\n";

    EmergencyQueue q;

    q.treatPatient();       // empty test
    cout << endl;

    q.addPatient("P101", 3);
    q.addPatient("P102", 1);
    q.addPatient("P103", 2);
    q.addPatient("P104", 3);
    cout << endl;
    q.display();
    cout << endl;

    q.treatPatient();       // P102 first (priority 1)
    q.treatPatient();       // then P103
    cout << endl;
    q.display();
    cout << endl;

    q.treatPatient();
    q.treatPatient();
    q.treatPatient();       // empty again

    return 0;
}
