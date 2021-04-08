/*
   SUBMITTED BY:  Lucas Vukotic
   DATE:          October 29, 2020
*/

#include <iostream>
#include <UtilitiesSYS.h>
#include <GamePM.h>

using namespace std;



int main()
{
    chcp1252();
    mainGamePM();
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
    string name;
    cout << "Name of the file without the extension" << endl;
    cout << "Name: ";
    cin >> name;
}
void show(tGamePM const &pm){

}
bool play(tGamePM &pm){

}
bool action(tGamePM &pm){
    
}
