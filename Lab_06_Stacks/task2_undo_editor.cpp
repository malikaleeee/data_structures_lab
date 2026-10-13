// Lab 06 - Lab Task 2: Undo Operation in a Text Editor (Stack using Array, OOP)
#include <iostream>
#include <string>
using namespace std;

class UndoStack
{
private:
    static const int SIZE = 10; // Maximum actions stored
    string actions[SIZE];       // Array that stores actions
    int top;                    // Index of the latest action

public:
    // Constructor: no actions yet
    UndoStack()
    {
        top = -1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isFull()
    {
        return top == SIZE - 1;
    }

    // PUSH: record a new action
    void push(string action)
    {
        if (isFull())
        {
            cout << "Stack Overflow! Cannot record: " << action << endl;
            return;
        }
        top++;
        actions[top] = action;
        cout << "Action performed: " << action << endl;
    }

    // POP: Undo the latest action
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! Nothing to undo." << endl;
            return;
        }
        cout << "Undo: " << actions[top] << endl;
        top--;
    }

    // PEEK: show the latest action
    void peek()
    {
        if (isEmpty())
        {
            cout << "No actions. Stack is empty." << endl;
            return;
        }
        cout << "Current TOP action: " << actions[top] << endl;
    }

    // DISPLAY: show actions from TOP to bottom
    void display()
    {
        if (isEmpty())
        {
            cout << "No actions. Stack is empty." << endl;
            return;
        }
        for (int i = top; i >= 0; i--)
        {
            cout << "  " << actions[i];
            if (i == top)
                cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main()
{
    UndoStack editor;

    // 1. Push actions
    cout << "--- Performing actions ---" << endl;
    editor.push("Type \"Hello\"");
    editor.push("Type \"World\"");
    editor.push("Add \"!\"");
    editor.push("Delete \"!\"");

    // 2. Display all actions from TOP to bottom
    cout << "\n--- All actions (TOP to bottom) ---" << endl;
    editor.display();

    // 3. Two POPs to simulate Undo
    cout << "\n--- Pressing Undo twice ---" << endl;
    editor.pop();
    editor.pop();

    // 4. Display the current TOP action
    cout << "\n--- Current action ---" << endl;
    editor.peek();

    // 5. Display the remaining actions
    cout << "\n--- Remaining actions (TOP to bottom) ---" << endl;
    editor.display();

    return 0;
}
