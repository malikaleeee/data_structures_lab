#include <iostream>
using namespace std;

class Node
{
public:
    int rollNumber;
    Node* next;
};

void addStudent(Node*& head, int rollNumber)
{
    Node* newNode = new Node();

    newNode->rollNumber = rollNumber;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return;
    }

    Node* current = head;

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newNode;
}

void displayStudents(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {
        cout << current->rollNumber;

        if (current->next != NULL)
        {
            cout << " -> ";
        }

        current = current->next;
    }

    cout << endl;
}

void searchStudent(Node* head, int rollNumber)
{
    Node* current = head;

    while (current != NULL)
    {
        if (current->rollNumber == rollNumber)
        {
            cout << "Student Found" << endl;
            return;
        }

        current = current->next;
    }

    cout << "Student Not Found" << endl;
}

int main()
{
    Node* head = NULL;

    addStudent(head, 101);
    addStudent(head, 105);
    addStudent(head, 108);
    addStudent(head, 112);

    cout << "Registered Students:" << endl;
    displayStudents(head);

    int rollNumber;

    cout << "Enter Roll Number to Search: ";
    cin >> rollNumber;

    searchStudent(head, rollNumber);

    return 0;
}