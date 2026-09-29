#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string productID;
    Node* next;
};

void addProduct(Node*& head, string productID)
{
    Node* newNode = new Node();

    newNode->productID = productID;
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

void displayCart(Node* head)
{
    Node* current = head;

    while (current != NULL)
    {
        cout << current->productID;

        if (current->next != NULL)
        {
            cout << " -> ";
        }

        current = current->next;
    }

    cout << endl;
}

void removeProduct(Node*& head, string productID)
{
    if (head == NULL)
    {
        return;
    }

    if (head->productID == productID)
    {
        Node* temp = head;

        head = head->next;

        delete temp;

        return;
    }

    Node* current = head;

    while (current->next != NULL)
    {
        if (current->next->productID == productID)
        {
            Node* temp = current->next;

            current->next = current->next->next;

            delete temp;

            return;
        }

        current = current->next;
    }
}

int main()
{
    Node* head = NULL;

    addProduct(head, "P101");
    addProduct(head, "P205");
    addProduct(head, "P310");
    addProduct(head, "P415");

    cout << "Shopping Cart:" << endl;
    displayCart(head);

    string productID;

    cout << "Remove Product: ";
    cin >> productID;

    removeProduct(head, productID);

    cout << "Updated Cart:" << endl;
    displayCart(head);

    return 0;
}