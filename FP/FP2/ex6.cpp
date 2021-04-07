/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          March 1, 2020
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

tColor mostUsedColor(const tScreen& screen, int row);
void firstBlink(const tScreen& screen, int& row, int& column);
void init(tScreen& screen);
string colorToString(tColor color);

int main()
{
    tScreen screen;
    int row = 3, column;
    tColor color;
    init(screen);
    color = mostUsedColor(screen, row);
    cout << "Most Used Color is " << colorToString(color) << endl;
    firstBlink(screen, row, column);
    cout << "First blinking pixel is in position " << row << " " << column << endl;
    return 0;
}

string colorToString(tColor color){
    string result = "";
    switch (color) {
        case 0: 
            result = "black"; 
            break;
        case 1: 
            result = "blue"; 
            break;
        case 2: 
            result = "green"; 
            break;
        case 3: 
            result = "yellow"; 
            break;
        case 4: 
            result = "red"; 
            break;
    }
    return result;
}

void init(tScreen& screen){
    tPixel pixel;
    pixel.blink = false;
    pixel.chr = 'c';
    pixel.color = red;

    for (int i = 0; i < RowLen; i++) {
        for (int j = 0; j < ColumnLen; j++) {
            screen[j][i] = pixel;
        }
    }
    screen[0][4] = tPixel{'y', green, true};
}

tColor mostUsedColor(const tScreen& screen, int row){
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
void firstBlink(const tScreen& screen, int& row, int& column){
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
    if (!found)
        row = column = -1;
}