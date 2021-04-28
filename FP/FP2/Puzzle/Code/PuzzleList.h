#ifndef PUZZLELIST_H
#define PUZZLELIST_H
#include "Puzzle.h"

const int MAX_PUZZLES = 100;

typedef tPuzzlePtr *Puzzle;

struct tPuzzlesList {
	// This list is always kept ordered in increasing order of the maximum number  of  attempts  to  complete  the  puzzle
	int count; 
	tPuzzlePtr[MAX_PUZZLES] data;
}

const int nDimensions = 2;

typedef tPuzzlesList tGatheredPuzzles[nDimensions];


void initialize(t GatheredPuzzles& gp);
bool load(t GathertedPuzzles& gp);
void save(const tGatheredPuzzles& gp);
int choosePuzzle(const PuzzlesList& pl);
bool sortedInsert(const PuzzlesList& pl, tPuzzle* p);
bool find(const tPuzzlesList& pl, tPuzzle* p, int& pos);

#endif
