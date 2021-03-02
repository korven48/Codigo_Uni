/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          Dicember 9, 2020
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>

using namespace std;

const int MAX = 30;
const string FileName = "list.txt";

typedef string tNames[MAX];
typedef double tMarks[MAX];

void load(tNames names, tMarks marks, int &counter);
int menu();
void display(const tNames names, const tMarks marks, int counter);
void insertStudent(tNames names, tMarks marks, int &counter);
void locate(const tNames names, const tMarks marks, int counter);
void deleteStudent(tNames names, tMarks marks, int &counter);

int main()
{
    tNames names;
    tMarks marks;
    int counter = 0, option;
    load(names, marks, counter);
    option = menu();
    while (option != 0)
    {
        switch (option)
        {
        case 1:
            cout << "Counter: " << counter << endl;
            display(names, marks, counter);
            break;
        case 2:
            insertStudent(names, marks, counter);
            break;
        case 3:
            locate(names, marks, counter);
            break;
        case 4:
            deleteStudent(names, marks, counter);
            break;
        case 0:
            break;
        }
        option = menu();
    }

    return 0;
}

void load(tNames names, tMarks marks, int &counter)
{
    ifstream inputFile(FileName);
    string name;
    double mark;
    if (!inputFile.is_open())
        cout << "File not found..." << endl;
    else
    {
        getline(inputFile, name);
        while (name != "XXX")
        {
            inputFile >> mark;
            inputFile.get();
            names[counter] = name;
            marks[counter] = mark;
            counter++;
            getline(inputFile, name);
        }
        inputFile.close();
    }
}

int menu()
{
    int option;
    cout << endl;
    cout << "1 - Display the list" << endl;
    cout << "2 - Insert a new student" << endl;
    cout << "3 - Locate a student" << endl;
    cout << "4 - Delete a student" << endl;
    cout << "0 - Exit" << endl;
    cout << "Your option: ";
    cin >> option;

    if (option > 4 || option < 0)
    {
        cout << endl
             << "Invalid option!" << endl;
        option = menu();
    }
    return option;
}

void display(const tNames names, const tMarks marks, int counter)
{
    for (int i = 0; i < counter; i++)
    {
        cout << setw(3) << right << (i + 1) << "   " << setw(30) << left << names[i]
             << right << fixed << setprecision(2) << marks[i] << endl;
    }
}

void insertStudent(tNames names, tMarks marks, int &counter)
{
    int pos;
    string name;
    double mark;
    if (counter < MAX)
    {
        // I prefer the if statement, but
        assert(counter < MAX);
        // it was proposed in the pdf
        cout << "Student's name: ";
        cin >> name;
        cout << "Student's grade: ";
        cin >> mark;
        cout << "Position in the list [1.." << counter << "]: ";
        cin >> pos;
        pos--;
        for (int i = counter; i >= pos; i--)
        {
            names[i + 1] = names[i];
            marks[i + 1] = marks[i];
        }
        names[pos] = name;
        counter++;
    }
    else
    {
        cout << "List is full" << endl;
    }
}

void locate(const tNames names, const tMarks marks, int counter)
{
    string match;
    cout << "Student's name: ";
    cin.get();
    getline(cin, match);
    int pos = -1;
    for (int i = 0; i < counter; i++)
    {
        if (names[i] == match)
            pos = i;
    }
    if (pos != -1)
        cout << "Found in position " << (pos + 1) << endl;
    else
        cout << "Not found" << endl;
}

void deleteStudent(tNames names, tMarks marks, int &counter)
{
    int pos;
    cout << "Position of the element to delete [1.." << counter << "]: ";
    cin >> pos;
    assert(pos >= 1 && pos <= counter);
    pos--;
    for (int i = pos; i < counter; i++)
    {
        names[i] = names[i + 1];
        marks[i] = marks[i + 1];
    }
    counter--;
}
