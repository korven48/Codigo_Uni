/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <UtilitiesSYS.h>
#include <GamePM.h>
#include <Matrix.h>

using namespace std;



int main()
{
    // chcp1252();
    // mainGamePM();
    tGamePM pm;
    load(pm);
    show(pm);
    return 0;
}

void mainGamePM(){

}

int menu()
{
    int option = 0;
    cout << "1 Version of the game - 1D" << endl;
    cout << "2 Version of the game - 2D" << endl;
    cout << "0 Exit" << endl;
    cout << "Select an option: ";
    cin >> option;
    return option;
}


bool initiate(tGamePM &pm, string mode, int num){

}
bool load(tGamePM &pm){
    int mode, attempts;
    string filename;
    ifstream in;
    mode = menu();
    pm.mode = mode;
    cout << "Name of the file without the extension" << endl;
    cout << "Name: ";
    cin >> filename;
    filename = filename + string("_") + char('0' + mode) + 'D';
    in.open(filename);
    if (in.is_open()){
        load(pm.initial, in);
        load(pm.objective, in);
        in >> attempts;
    }
    pm.attempts = attempts;
}
void show(tGamePM const &pm){
    for (int i = 0; i < pm.initial.height; i++)
        for (int j=0; j < pm.initial.width; j++)
            cout << pm.initial.image[i][j] << endl;
}
bool play(tGamePM &pm){

}
bool action(tGamePM &pm){
    
}
