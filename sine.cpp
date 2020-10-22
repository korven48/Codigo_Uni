/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 19, 2020
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    const int lines = 21, height = 15, increment = 18; // increment in degrees
    const double PI = 3.1415926535897, degrees2rad = PI / 180;

    int x = 0, line = 0, degrees = 0;
    while (line < lines){
        int pos = height + x;
        cout << setw(pos) << "*" << endl;
        degrees += increment;
        x = lround(height * sin(degrees* degrees2rad));
        line++;
    }

    return 0;
}
