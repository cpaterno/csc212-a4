#include "board.h"

#include <cmath>

Board::Board() {
	dim = 0; 
	N = 0; 
	gB = nullptr; 
	dType = 0; 
	dist = 0; 
	mov = 0; 
	zRow = 0;
	zCol = 0; 
	inver = 0;
}       

Board::Board(const unsigned int *b, unsigned int n, unsigned int m, char type) {
	unsigned int index = 0;
	dim = sqrt(n + 1);
	N = n;
	dType = type;
	mov = m;
	dist = 0; // initialize dist
	zRow = 0; // initialize zRow
	zCol = 0;

	// setup the board
	gB = new unsigned int[N + 1];
	// fill in its values
	for(unsigned int i = 0; i < (N + 1); i++) {
		gB[i] = b[i];
		if (b[i] == 0) index = i;
	}
	zRow = index / dim;
	zCol = abs(index - ((int)zRow * dim));
	// update dist
	if (dType == 'm') dist = calcMan();
	else if (dType == 'b') dist = calcHam();
	inver = countInvers();
}

Board::~Board() {
	delete[] gB;
}

bool Board::is_solvable() {
	if (dim % 2 != 0 && inver % 2 == 0) return true;
	else if (dim % 2 == 0 && (inver + zRow) % 2 != 0) return true;
    return false;
}

bool Board::is_goal() {
	if (dist == 0) return true;
    return false;
}
        
void Board::neighbors(std::vector<Board *> *neigh, char type) {
	
}
        
unsigned int Board::get_n_moves() {
    return mov;
}        

unsigned int Board::calcHam() {
	unsigned int ham = 0;
	for(unsigned int i = 0; i < (N + 1); i++) {
		if (gB[i] != 0 && gB[i] != i + 1) ham++;
	}
	return ham;
}

unsigned int Board::hamming() {
    return dist;
}

unsigned int Board::calcMan() {
	unsigned int man = 0;
	int index = 0;
	int sR = 0;
	int sC = 0;
	int aR = 0;
	int aC = 0;
	// taking advantage of index = r * dim + c formula
	for(unsigned int i = 0; i < (N + 1); i++) {
		// ignore the empty element
		if (gB[i] == 0) continue;
		index = gB[i] - 1;
		// if the element is in the right space, no need to do any calculations
		if ((int)i == index) continue; 
		sR = index / dim;
		sC = abs(index - (sR * dim));
		aR = i / dim;
		aC = abs(i - (aR * dim));
		man += abs(sR - aR) + abs(sC - aC);
	}
	return man;
}

unsigned int Board::manhattan() {
    return dist;
}

unsigned int Board::countInvers() {
	unsigned int count = 0;
	for(unsigned int i = 0; i < (N + 1); i++) {
		for(unsigned int j = i + 1; j < (N + 1); j++) {
			if (gB[i] > gB[j]) count++;
		}
	}
    return count;	
}


unsigned int Board::inversions() {
	return inver;
}

unsigned int Board::getZRow() {
	return zRow;
}

unsigned int Board::getZCol() {
	return zCol;
}
