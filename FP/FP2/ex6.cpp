/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>

using namespace std;

const int RowLen = 80;
const int ColumnLen = 25;
const int ColorNum = 5;

enum tColor{
    black = 0,
    blue, 
    green, 
    yellow,
    red
};

struct tPixel{
    char chr;
    tColor color;
    bool blink;
};

typedef tPixel tPixelRow[RowLen];
typedef tPixelRow tScreen[ColumnLen];

typedef int tCountColors[ColorNum];

tColor mostUsedColor(tScreen& screen, int row);
void firstBlink(tScreen& screen, int& row, int& column);

int main()
{
    tScreen screen;
    int row = 3, column;
    mostUsedColor(screen, row);
    firstBlink(screen, row, column);
    cout << row << " " << column << endl;
    return 0;
}

tColor mostUsedColor(tScreen& screen, int row){
    tColor color;
    tCountColors nColors;
    int index, max;
    for (int i = 0; i < ColorNum; i++)
        nColors[i] = 0;

    for (int col = 0; col < ColumnLen; col++){
        index = screen[col][row].color;
        nColors[index]++;
    }
    max = -1;
    for (int i = 0; i < ColorNum; i++){
        if (nColors[i] > max){
            max = nColors[i];
            color = tColor(i);
        }
    }
    return color;
}
void firstBlink(tScreen& screen, int& row, int& column){
    bool found = false;
    row = 0;
    while (row < RowLen && !found){
        column = 0;
        while (column < ColumnLen && !found){
            if (screen[column][row].blink)
                found = true;
            else
                ++column;
        }
        if (!found)
            ++row;
    }
}