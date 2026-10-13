// Lab 06 - Lab Task 4: Restaurant Order Processing (Stack using Singly Linked List, OOP)
#include <iostream>
#include <string>
using namespace std;

// One order in the stack
class Node
{
public:
    string orderID;
    Node* next;

    Node(string id)
    {
        orderID = id;
        next = NULL;
    }
};

class OrderStack
{
private:
    Node* top; // Latest order

public:
    // Constructor: no orders yet
    OrderStack()
    {
        top = NULL;
    }

    // Destructor: free remaining nodes
    ~OrderStack()
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

    // PUSH: store a new order
    void push(string id)
    {
        Node* newNode = new Node(id);
        newNode->next = top; // new order sits on top of the old TOP
        top = newNode;       // new order becomes TOP
        cout << "Order placed: " << id << endl;
    }

    // POP: process the latest order
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! No orders to process." << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        cout << "Processing order: " << temp->orderID << endl;
        delete temp;
    }

    // PEEK: show the latest order
    void peek()
    {
        if (isEmpty())
        {
            cout << "No orders. Stack is empty." << endl;
            return;
        }
        cout << "Current TOP order: " << top->orderID << endl;
    }

    // DISPLAY: show orders from TOP to bottom
    void display()
    {
        if (isEmpty())
        {
            cout << "No orders. Stack is empty." << endl;
            return;
        }
        Node* current = top;
        while (current != NULL)
        {
            cout << "  " << current->orderID;
            if (current == top)
                cout << "   <-- TOP";
            cout << endl;
            current = current->next;
        }
    }
};

int main()
{
    OrderStack restaurant;

    // 1. Push order IDs
    cout << "--- Receiving orders ---" << endl;
    restaurant.push("ORD-101");
    restaurant.push("ORD-102");
    restaurant.push("ORD-103");
    restaurant.push("ORD-104");

    // 2. Display all orders from TOP to bottom
    cout << "\n--- All orders (TOP to bottom) ---" << endl;
    restaurant.display();

    // 3. Two POPs to process two orders
    cout << "\n--- Processing two orders ---" << endl;
    restaurant.pop();
    restaurant.pop();

    // 4. Display the current TOP order
    cout << "\n--- Current TOP order ---" << endl;
    restaurant.peek();

    // 5. Display the remaining orders
    cout << "\n--- Remaining orders (TOP to bottom) ---" << endl;
    restaurant.display();

    // 6. Check whether the stack is empty
    cout << "\n--- Is the stack empty? ---" << endl;
    if (restaurant.isEmpty())
        cout << "Yes, the stack is empty." << endl;
    else
        cout << "No, the stack is not empty." << endl;

    return 0;
}
