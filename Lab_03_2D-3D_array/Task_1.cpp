#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int marks[6][4] =
    {
        {85, 90, 88, 92},
        {78, 82, 80, 85},
        {92, 95, 94, 96},
        {70, 75, 72, 78},
        {88, 86, 90, 89},
        {80, 84, 83, 81}
    };

    string subjects[4] = {"English", "Mathematics", "Programming", "AI"};

    cout << "STUDENT MARKS ANALYSIS\n\n";

    cout << left << setw(12) << "Student";

    for (int j = 0; j < 4; j++)
        cout << setw(15) << subjects[j];

    cout << setw(10) << "Total" << "Average\n";

    for (int i = 0; i < 6; i++)
    {
        int total = 0;

        cout << left << setw(12) << "Student " + to_string(i + 1);

        for (int j = 0; j < 4; j++)
        {
            cout << setw(15) << marks[i][j];
            total += marks[i][j];
        }

        double average = total / 4.0;

        cout << setw(10) << total;
        cout << fixed << setprecision(2) << average << endl;
    }

    cout << "\nHighest Mark in Each Subject:\n";

    for (int j = 0; j < 4; j++)
    {
        int highest = marks[0][j];

        for (int i = 1; i < 6; i++)
        {
            if (marks[i][j] > highest)
                highest = marks[i][j];
        }

        cout << subjects[j] << ": " << highest << endl;
    }

    int highestTotal = 0;
    int highestStudent = 0;

    for (int i = 0; i < 6; i++)
    {
        int total = 0;

        for (int j = 0; j < 4; j++)
            total += marks[i][j];

        if (total > highestTotal)
        {
            highestTotal = total;
            highestStudent = i;
        }
    }

    cout << "\nStudent with Highest Total:\n";
    cout << "Student " << highestStudent + 1 << endl;
    cout << "Total: " << highestTotal << endl;

    return 0;
}