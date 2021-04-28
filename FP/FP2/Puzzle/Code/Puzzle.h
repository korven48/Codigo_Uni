#ifndef PUZZLE_H
#define	PUZZLE_H
#include "Matrix.h"

struct tPuzzle {
	string name;
	string file;
	string type;
	int maxMoves;

};

void mainPuzzle(tPuzzle& p);
bool load(tPuzzle& p, string type);
void show(const tPuzzle& p);
bool play(tPuzzle& p);
void action(tPuzzle& p);

#endif