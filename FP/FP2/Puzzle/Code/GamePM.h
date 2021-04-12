#ifndef GAMEPM_H
#define GAMEPM_H

#include <iostream>
#include "Matrix.h"

using namespace std;

struct tGamePM{
    int mode;
    int attempts;
    tMatrixChar initial;
    tMatrixChar objective;
};

void mainGamePM();
int menu();
bool initiate(tGamePM &pm, string mode, int num);
bool load(tGamePM &pm);
void show(tGamePM const &pm);
void displayImage(const tMatrixChar& img);
bool play(tGamePM &pm);
bool action(tGamePM &pm);

#endif