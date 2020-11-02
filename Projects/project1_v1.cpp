/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <ctime>
#include <cstdlib>

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

int main()
{
    short int tileN1, tileN2;
    int input;
    string lane;

    srand(time(NULL));

    input = menu();
    while (input != 0)
    {
        switch (input)
        {
        case 1: // ------------- Place a tile to the left -----------

            break;
        case 2: // ------------- Place a tile to the right ----------

            break;
        case 3: // ------------- Next tile --------------------------

            break;
        }

        input = menu();
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

    cout << lane << endl << endl;

    cout << "Tiles placed: " << placed << " - Tiles taken: " << taken << endl;
    cout << "Player's tile: " << tileToStr(tileN1, tileN2) << endl;
}

short int random()
{
    return rand() % 7;
}

string digitToStr(int digit)
{
    return string(1, '0' + digit);
}

bool canGoLeft(string lane, short int tileN1, short int tileN2)
{
}

bool canGoRight(string lane, short int tileN1, short int tileN2)
{
}

string placeTileLeft(string lane, short int tileN1, short int tileN2)
{
    // Check wich order is correct (1-2 or 2-1)
    return lane + tileToStr(tileN1, tileN2);
}

string placeTileRight(string lane, short int tileN1, short int tileN2)
{
    // Check wich order is correct (1-2 or 2-1)
    return tileToStr(tileN1, tileN2) + lane;
}