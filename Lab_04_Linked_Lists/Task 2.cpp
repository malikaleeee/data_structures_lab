#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string patientID;
    Node* next;
};

void addPatient(Node*& head, string patientID)
{
    Node* newNode = new Node();

    newNode->patientID = patientID;
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

void displayPatients(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {
        cout << current->patientID;

        if (current->next != NULL)
        {
            cout << " -> ";
        }

        current = current->next;
    }

    cout << endl;
}

void removeFirstPatient(Node*& head)
{
    if (head == NULL)
    {
        return;
    }

    Node* temp = head;

    head = head->next;

    delete temp;
}

int main()
{
    Node* head = NULL;

    addPatient(head, "P101");
    addPatient(head, "P102");
    addPatient(head, "P103");
    addPatient(head, "P104");

    cout << "Waiting Patients:" << endl;
    displayPatients(head);

    cout << "Patient " << head->patientID << " is being served." << endl;

    removeFirstPatient(head);

    cout << "Updated Queue:" << endl;
    displayPatients(head);

    return 0;
}