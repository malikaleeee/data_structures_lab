// Lab 06 - Lab Task 1: Browser Back History (Stack using Array, OOP)
#include <iostream>
#include <string>
using namespace std;

class BrowserHistory
{
private:
    static const int SIZE = 10; // Maximum pages the history can hold
    string pages[SIZE];         // Array that stores visited pages
    int top;                    // Index of the most recent page

public:
    // Constructor: history starts empty
    BrowserHistory()
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

    // PUSH: visit a new page
    void push(string page)
    {
        if (isFull())
        {
            cout << "Stack Overflow! History is full, cannot visit " << page << "." << endl;
            return;
        }
        top++;
        pages[top] = page;
        cout << "Visited: " << page << endl;
    }

    // POP: press the Back button
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow! No page to go back from." << endl;
            return;
        }
        cout << "Back pressed. Removed: " << pages[top] << endl;
        top--;
    }

    // PEEK: show the current page
    void peek()
    {
        if (isEmpty())
        {
            cout << "No current page. History is empty." << endl;
            return;
        }
        cout << "Current TOP page: " << pages[top] << endl;
    }

    // DISPLAY: show history from TOP to bottom
    void display()
    {
        if (isEmpty())
        {
            cout << "History is empty." << endl;
            return;
        }
        for (int i = top; i >= 0; i--)
        {
            cout << "  " << pages[i];
            if (i == top)
                cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main()
{
    BrowserHistory history;

    // 1. Push visited pages
    cout << "--- Visiting pages ---" << endl;
    history.push("Google");
    history.push("YouTube");
    history.push("Facebook");
    history.push("GitHub");

    // 2. Display all pages from TOP to bottom
    cout << "\n--- Browsing history (TOP to bottom) ---" << endl;
    history.display();

    // 3. One POP to simulate the Back button
    cout << "\n--- Pressing Back ---" << endl;
    history.pop();

    // 4. Display the current TOP page
    cout << "\n--- Current page ---" << endl;
    history.peek();

    // 5. Display the remaining browsing history
    cout << "\n--- Remaining history (TOP to bottom) ---" << endl;
    history.display();

    return 0;
}
