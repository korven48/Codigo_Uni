/*
   SUBMITTED BY:  Lucas Vukotic and Iván Gallego
   DATE:          April 4, 2021
*/

#include <iostream>
#include <iomanip>
#include "UtilitiesSYS.h"
#include "GamePM.h"
#include "Matrix.h"

using namespace std;

int main()
{
    chcp1252();
    mainGamePM();
    return 0;
}

void mainGamePM(){
    bool loaded, win;
    tGamePM pm;
  

    do {
        loaded = load(pm);
        if (pm.mode == 0) {
            cout << "Exiting puzzle..." << endl;
        }
        else if (!loaded) {
            cout << "File doesn't exist, exiting..." << endl;
            pm.mode = 0;
        }
        else{
            win = play(pm);
            if (win)
                cout << "Congratulations, you have solved the puzzle!" << endl << endl;
            else
                cout << "You lost, try again..." << endl << endl;
        }
        
    } while (pm.mode != 0);
}

int menu()
{
    int option = 0;
    cout << "1 Version of the game - 1D" << endl;
    cout << "2 Version of the game - 2D" << endl;
    cout << "0 Exit" << endl;
    cout << "Select an option: ";
    cin >> option;
    cout << endl;
    return option;
}
bool initiate(tGamePM& pm, string mode, int num) {
    // I just don´t know what should this function do and I found no use for it
    return false;
}
bool load(tGamePM &pm){
    bool ok = false;
    int attempts;
    string filename;
    ifstream in;
    pm.mode = menu();
    if (pm.mode != 0) {
        cout << "Name of the file without the extension" << endl;
        cout << "Name: ";
        cin >> filename;
        cout << endl;
        filename = string("Files/") + filename + '_' + char('0' + pm.mode) + 'D' + string(".txt");
        in.open(filename);
        if (in.is_open()){
            load(pm.initial, in);
            load(pm.objective, in);
            in >> attempts;
            pm.attempts = attempts;
            ok = true;
            cout << "You have " << pm.attempts << " attempts!" << endl;
        }
    }
    return ok;
}
void show(tGamePM const &pm){
    displayImage(pm.initial);
    displayImage(pm.objective);
    cout << "You have " << pm.attempts << " attempts left." << endl << endl;
}
void displayImage(const tMatrixChar& img) {
    cout << "   ";
    for (int i = 0; i < img.width; i++)
        cout << setw(2) << i;
    cout << endl;
    for (int i = 0; i < img.height; i++) {
        cout << setw(3) << left << i;
        for (int j = 0; j < img.width; j++) {
            colorCTA(7, img.image[i][j] - '0');
            cout << "  ";
        }
        colorCTA(7, 0);
        cout << endl;
    }
    cout << endl << endl;
}
bool play(tGamePM& pm) {
    bool win = false, validAction;
    show(pm);
    while (pm.attempts > 0 && !win) {
        
        validAction = action(pm);
        while (!validAction) {
            cout << "Non valid action, retry with a valid action" << endl;
            validAction = action(pm);
        }
        pm.attempts--;
        
        show(pm);

        if (pm.initial == pm.objective)
            win = true;
        
    }
    return win;
}

bool action(tGamePM& pm) {
    bool ok = true;
    string action;
    cout << "Insert your action: ";
    cin >> action;
    if (pm.mode == 1)
        ok = action1D(pm.initial, action);
    else
        ok = action2D(pm.initial, action);
    return ok;
}

bool action1D(tMatrixChar& image, string action) {
    bool ok = true;
    int a, b, c, d;

    if (action == "RS") {
        cin >> a >> b;
        ok = swapR(image, a, b);
    }
    else if (action == "CS") {
        cin >> a >> b;
        ok = swapC(image, a, b);
    }
    else if (action == "DS") {
        cin >> a;
        ok = swapD(image, a);
    }
    else if (action == "RF") {
        cin >> a;
        ok = flipR(image, a);
    }
    else if (action == "CF") {
        cin >> a;
        ok = flipC(image, a);
    }
    else if (action == "DF") {
        cin >> a;
        ok = flipD(image, a);
    }
    else {
        ok = false;
    }

    return ok;
}

bool action2D(tMatrixChar& image, string action) {
    bool ok = true;
    int a, b, c, d;

    if (action == "VF") {
        flipV(image);
    }
    else if (action == "HF") {
        flipH(image);
    }
    else if (action == "RR") {
        rotateR(image);
    }
    else if (action == "NS") {
        cin >> a >> b >> c >> d;
        tCoor pos1, pos2;
        pos1.x = a;
        pos1.y = b;
        pos2.x = c;
        pos2.y = d;
        ok = swapAdj(image, pos1, pos2);
    }
    else if (action == "DF") {
        ok = flipID(image);
    }
    else {
        ok = false;
    }
    return ok;
}