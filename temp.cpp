#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

string digitToStr(int digit)
{
    return string(1, '0' + digit);
}

string tileToStr(short int left, short int right)
{
    string tile = "|";
    tile += digitToStr(left) + string("-") + digitToStr(right) + string("|");
    return tile;
}

string placeTileLeft(string lane, short int tileN1, short int tileN2)
{
    return lane + tileToStr(tileN1, tileN2);
}

int main(int argc, char const *argv[])
{
    int x;
    char chr = 65;
    string lane = "|1-2||2-3||3-9|";
    double d;

    cout << placeTileLeft(lane, 2, 9) << endl;
    return 0;
}

    