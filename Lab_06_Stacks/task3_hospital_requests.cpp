// Lab 06 - Lab Task 3: Hospital Patient Emergency Requests (Stack using Singly Linked List, OOP)
#include <iostream>
#include <string>
using namespace std;

// One request in the stack
class Node
{
public:
    string patientID;
    Node* next;

    Node(string id)
    {
        patientID = id;
        next = NULL;
    }
};

class RequestStack
{
private:
    Node* top; // Latest request

public:
    // Constructor: no requests yet
    RequestStack()
    {
        top = NULL;
    }

    // Destructor: free remaining nodes
    ~RequestStack()
    {
        while (top != NULL)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty()
    {
        return top == NULL;
    }

    // PUSH: receive a new request
    void push(string id)
    {
        Node* newNode = new Node(id);
        newNode->next = top; // new request sits on top of the old TOP
        top = newNode;       // new request becomes TOP
        cout << "Request received: " << id << endl;
    }

    // POP: handle the latest request
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! No requests to handle." << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << "Handling request: " << temp->patientID << endl;
        delete temp;
    }

    // PEEK: show the latest request
    void peek()
    {
        if (isEmpty())
        {
            cout << "No requests. Stack is empty." << endl;
            return;
        }
        cout << "Current TOP request: " << top->patientID << endl;
    }

    // DISPLAY: show requests from TOP to bottom
    void display()
    {
        if (isEmpty())
        {
            cout << "No requests. Stack is empty." << endl;
            return;
        }
        Node* current = top;
        while (current != NULL)
        {
            cout << "  " << current->patientID;
            if (current == top)
                cout << "   <-- TOP";
            cout << endl;
            current = current->next;
        }
    }
};

int main()
{
    RequestStack hospital;

    // 1. Push patient request IDs
    cout << "--- Receiving emergency requests ---" << endl;
    hospital.push("P101");
    hospital.push("P102");
    hospital.push("P103");
    hospital.push("P104");

    // 2. Display all requests from TOP to bottom
    cout << "\n--- All requests (TOP to bottom) ---" << endl;
    hospital.display();

    // 3. One POP to handle the latest request
    cout << "\n--- Handling latest request ---" << endl;
    hospital.pop();

    // 4. Display the new TOP request
    cout << "\n--- New TOP request ---" << endl;
    hospital.peek();

    // 5. Display the remaining requests
    cout << "\n--- Remaining requests (TOP to bottom) ---" << endl;
    hospital.display();

    return 0;
}
