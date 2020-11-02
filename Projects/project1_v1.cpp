/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cctype>

using namespace std;

int menu();
string tileToStr(short int left, short int right);
void displayTable(short int tileN1, short int tileN2, string lane, int placed, int taken);
short int random();
string digitToStr(int digit);
bool canGoLeft(string lane, short int tileN1, short int tileN2);
bool canGoRight(string lane, short int tileN1, short int tileN2);
string placeTileLeft(string lane, short int tileN1, short int tileN2);
string placeTileRight(string lane, short int tileN1, short int tileN2);

bool askUser(string str);

// =============================
//     GLOBAL VARIABLE
short int maxTile;
// =============================

int main()
{
    short int tileN1, tileN2;
    int option, placed, taken;
    string lane, fileName;
    bool take;

    ofstream outputFile;
    ifstream inputFile;

    srand(time(NULL));

    if (askUser("Do you want to resume a saved game [Y/N]? "))
    {
        cout << "Please enter the file name: ";
        cin.get();
        getline(cin, fileName);
        inputFile.open(fileName);
        inputFile >> maxTile >> lane >> placed >> taken >> tileN1 >> tileN2;
        inputFile.close();
    }
    else
    {
        cout << "Please enter the maximum number for tile squares (3-9): ";
        cin >> maxTile;

        placed = 0;
        taken = 0;

        tileN1 = random();
        tileN2 = random();

        lane = tileToStr(random(), random());
    }

    displayTable(tileN1, tileN2, lane, placed, taken);
    option = menu();
    while (option != 0)
    {
        take = true;
        switch (option)
        {
        case 1: // ------------- Place a tile to the left -----------
            if (canGoLeft(lane, tileN1, tileN2))
            {
                lane = placeTileLeft(lane, tileN1, tileN2);
                placed++;
            }
            else
            {
                cout << "Not possible!" << endl;
                cout << "Press any key to continue..." << endl;
                take = false;
            }
            break;
        case 2: // ------------- Place a tile to the right ----------
            if (canGoRight(lane, tileN1, tileN2))
            {
                lane = placeTileRight(lane, tileN1, tileN2);
                placed++;
            }
            else
            {
                cout << "Not possible!" << endl;
                cout << "Press any key to continue..." << endl;
                take = false;
            }
            break;
        case 3: // ------------- Next tile --------------------------

            break;
        }

        if (take)
        {
            tileN1 = random();
            tileN2 = random();
            taken++;
        }

        displayTable(tileN1, tileN2, lane, placed, taken);
        option = menu();
    }

    if (askUser("Do you want to save the game [Y/N]? "))
    {
        cout << "Enter a file name: " << endl;
        cin >> fileName;
        outputFile.open(fileName);
        outputFile << maxTile << endl
                   << lane << endl
                   << placed << endl
                   << taken << endl
                   << tileN1 << endl
                   << tileN2 << endl;
        outputFile.close();
    }

    return 0;
}

int menu()
{
    int input;

    cout << " ------------------ " << endl;
    cout << "|"
         << "  O P T I O N S  "
         << "|" << endl;
    cout << " ------------------ " << endl;

    cout << "1. Place a tile to the left" << endl;
    cout << "2. Place a tile to the right" << endl;
    cout << "3. Next tile" << endl;
    cout << "0. Exit" << endl;

    cout << "Your option: ";
    cin >> input;

    return input;
}

string tileToStr(short int left, short int right)
{
    string tile = "|";

    // Tile: |left‐right| (e.g |2-5|)
    tile += digitToStr(left) + string("-") + digitToStr(right) + string("|");
    return tile;
}

void displayTable(short int tileN1, short int tileN2, string lane, int placed, int taken)
{
    cout << " ------------------ " << endl;
    cout << "|"
         << "    T A B L E    "
         << "|" << endl;
    cout << " ------------------ " << endl;

    cout << lane << endl
         << endl;

    cout << "Tiles placed: " << placed << " - Tiles taken: " << taken << endl;
    cout << "Player's tile: " << tileToStr(tileN1, tileN2) << endl;
}

short int random()
{
    return rand() % (maxTile + 1);
}

string digitToStr(int digit)
{
    return string(1, '0' + digit);
}

int chrToInt(char ch)
{
    return ch - '0';
}

bool canGoLeft(string lane, short int tileN1, short int tileN2)
{
    int leftMostNumber = chrToInt(lane[1]);

    return leftMostNumber == tileN1 || leftMostNumber == tileN2;
}

bool canGoRight(string lane, short int tileN1, short int tileN2)
{
    int rightMostNumber = chrToInt(lane[lane.size() - 2]);

    return rightMostNumber == tileN1 || rightMostNumber == tileN2;
}

string placeTileLeft(string lane, short int tileN1, short int tileN2)
{
    int leftMostNumber = chrToInt(lane[1]);
    if (leftMostNumber == tileN1)
        lane = tileToStr(tileN2, tileN1) + lane;
    else
        lane = tileToStr(tileN1, tileN2) + lane;

    return lane;
}

string placeTileRight(string lane, short int tileN1, short int tileN2)
{
    int rightMostNumber = chrToInt(lane[lane.size() - 2]);
    if (rightMostNumber == tileN1)
        lane += tileToStr(tileN1, tileN2);
    else
        lane += tileToStr(tileN2, tileN1);

    return lane;
}

bool askUser(string str)
{
    char answer;

    cout << str;
    cin >> answer;

    return toupper(answer) == 'Y';
}