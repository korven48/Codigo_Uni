/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <iomanip>
#include "UtilitiesSYS.h"
#include "GamePM.h"
#include "Matrix.h"

using namespace std;

void printColor(int color) {
    colorCTA(0, color);
    cout << "  ";
    colorCTA(7, 0);
}

//int main() {
//    tGamePM pm;
//
//    load(pm);
//    show(pm);
//    tCoor pos1, pos2;
//    pos1.x = 0;
//    pos1.y = 0;
//    pos2.x = 0;
//    pos2.y = 1;
//    swap(pm.initial, pos1, pos2);
//    swapR(pm.initial, 0, 1);
//    show(pm);
//    return 0;
//}

int main()
{
    chcp1252();
    mainGamePM();
    return 0;
}

void mainGamePM(){
    bool win;
    tGamePM pm;
  
    load(pm);
    while (pm.mode != 0)
    {
        win = play(pm);
        if (win)
            cout << "Congratulations, you have solved the puzzle!" << endl << endl;
        else
            cout << "Try again..." << endl << endl;
        load(pm);
    }
}

int menu()
{
    int option = 0;
    cout << "1 Solve a 1D puzzle" << endl; 
    cout << "2 Solve a 2D puzzle" << endl;
    cout << "3 Add a puzzle to the catalog" << endl;
    cout << "0 Exit" << endl;
    cout << "Select an option: ";
    cin >> option;
    cout << endl;
    return option;
}
bool initiate(tGamePM &pm, string mode, int num);
bool load(tGamePM &pm){
    bool ok = false;
    int mode, attempts;
    string filename;
    ifstream in;
    mode = menu();
    pm.mode = mode;
    if (mode != 0) {
        cout << "Name of the file without the extension" << endl;
        cout << "Name: ";
        cin >> filename;
        cout << endl;
        filename = string("Files/") + filename + string("_") + char('0' + mode) + 'D' + string(".txt");
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
    cout << "You have " << pm.attempts << " attempts left." << endl;
    cout << endl;

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
            //cout << img.image[i][j];
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

        if (pm.initial == pm.objective) {
            win = true;
        }
        
    }
    return win;
}

bool action(tGamePM& pm) {
    bool ok = true;
    string action;
    int a, b, c, d;
    cout << "Insert your action: ";
    cin >> action;
    // Still need to check if action corresponds with mode 
    if (action == "RS") {
        cin >> a >> b;
        ok = swapR(pm.initial, a, b);
    } 
    else if (action == "CS"){
        cin >> a >> b;
        ok = swapC(pm.initial, a, b);
    }
    else if (action == "DS"){
        cin >> a;
        ok = swapD(pm.initial, a);
    }
    else if (action == "RF"){
        cin >> a;
        ok = flipR(pm.initial, a);
    }
    else if (action == "CF"){
        cin >> a;
        ok = flipC(pm.initial, a);
    }
    else if (action == "DF" && pm.mode == 1) {
        cin >> a;
        ok = flipD(pm.initial, a);
    }
    // 2D
    else if (action == "VF") {
        flipV(pm.initial);
    }
    else if (action == "HF") {
        flipH(pm.initial);
    }
    else if (action == "RR") {
        rotateR(pm.initial);
    }
    else if (action == "NS") {
        cin >> a >> b >> c >> d;
        tCoor pos1, pos2;
        pos1.x = a;
        pos1.y = b;
        pos2.x = c;
        pos2.y = d;
        ok = swapAdj(pm.initial, pos1, pos2);
    }
    else if (action == "DF") {
        ok = flipID(pm.initial);
    }
    else {
        ok = false;
    }

    return ok;
}
