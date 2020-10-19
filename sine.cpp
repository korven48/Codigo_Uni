
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    const int lines = 21, height = 15, increment = 18; // increment in degrees
    const double PI = 3.1415926535897, degrees2rad = PI / 180, radians2degrees = 180 / PI;

    int x = 0, i = 0;
    while (i < lines){
        int pos = height + x;
        cout << setw(pos) << "*" << endl;
        x += increment;
        x = lround(sin(x * degrees2rad));
    }
}
