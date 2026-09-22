#include <iostream>
using namespace std;

int main()
{
    int parking[4][5] =
    {
        {1, 0, 1, 0, 1},
        {0, 1, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1}
    };

    int occupied = 0;
    int empty = 0;

    cout << "PARKING MANAGEMENT SYSTEM\n\n";

    cout << "Parking Layout:\n";
    cout << "0 = Empty, 1 = Occupied\n\n";

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << parking[i][j] << " ";

            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;
        }

        cout << endl;
    }

    cout << "\nTotal Capacity: " << 20 << endl;
    cout << "Occupied Spaces: " << occupied << endl;
    cout << "Empty Spaces: " << empty << endl;

    int row, column;

    cout << "\nEnter row number (1-4): ";
    cin >> row;

    cout << "Enter column number (1-5): ";
    cin >> column;

    if (row >= 1 && row <= 4 && column >= 1 && column <= 5)
    {
        if (parking[row - 1][column - 1] == 1)
            cout << "The parking space is Occupied." << endl;
        else
            cout << "The parking space is Empty." << endl;
    }
    else
    {
        cout << "Invalid row or column." << endl;
    }

    return 0;
}