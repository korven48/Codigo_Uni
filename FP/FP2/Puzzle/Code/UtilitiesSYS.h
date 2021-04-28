//#pragma once
#ifndef UTILITIESSYS_H
#define UTILITIESSYS_H

typedef unsigned char uint8;  // Byte
//typedef unsigned short int usint; // small integer without sign

void chcp1252();
void clear_screen();
void pause();

void colorCTA(uint8 color, uint8 background);

#endif