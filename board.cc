#include "board.h"
#include <iostream>
#include <cmath>

void swap(unsigned int* a, unsigned int* b) {
	unsigned int temp = *a;
	*a = *b;
	*b = temp;
}

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

Board::Board(unsigned int *b, unsigned int n, unsigned int m, char type) {
	unsigned int index = 0;
	dim = sqrt(n);
	N = n;
	dType = type;
	mov = m;
	dist = 0; // initialize dist
	zRow = 0; // initialize zRow
	zCol = 0;
	inver = 0;
	if (!n) gB = nullptr;
	else {
		// setup the board
		gB = new unsigned int[N];
		// fill in its values
		for(unsigned int i = 0; i < N; i++) {
			gB[i] = b[i];
			if (b[i] == 0) index = i;
		}
		zRow = index / dim;
		zCol = abs(index - ((int)zRow * dim));
		// update dist
		if (dType == 'm') dist = calcMan();
		else if (dType == 'h') dist = calcHam();
		inver = countInvers();
	}
}

Board::~Board() {
	if (gB) delete[] gB;
}

bool Board::is_solvable() {
	if (dim % 2 != 0 && inver % 2 == 0) return true;
	else if (dim % 2 == 0 && (inver + zRow) % 2 != 0) return true;
    return false;
}

bool Board::is_goal() {
    return (dist == 0);
}
        
void Board::neighbors(std::vector<Board *> *neigh, char type) {
	if (!gB) return;
	bool direction[4] = {true, true, true, true};
	/* 3 cases:
		Corner: 2 neighbors
		Edge: 3 neighbors
		Else: 4 neighbors
	*/
	if ((zRow == 0 && zCol == 0) || (zRow == 0 && zCol == dim - 1) || (zRow == dim - 1 && zCol == 0) || (zRow == dim - 1 && zCol == dim - 1)) {
		// corners case
		if (zRow != zCol) {
			if (zRow == 0) {
				// up and right (top right corner)
				direction[1] = false;
				direction[2] = false;
			} else {
				// down and left (bottom left corner)
				direction[0] = false;
				direction[3] = false;
			}
		} else {
			if (zRow == 0) {
				// up and left (top left corner)
				direction[1] = false;
				direction[3] = false;
			} else {
				// down and right (bottom right corner)
				direction[0] = false;
				direction[2] = false;
			}
		}
	} else if (zRow == 0 || zCol == 0 || zRow == dim - 1 || zCol == dim - 1) {
		// edges case
		// up, left, right
		if (zRow == 0) direction[1] = false;
		// up, down, left	
		else if (zCol == 0) direction[3] = false;
		// down, left, right
		else if (zRow == dim - 1) direction[0] = false;
		// up, down, right	
		else direction[2] = false;
	} 

	if (direction[0]) {
		// swap up
		swap(&gB[zRow * dim + zCol], &gB[(zRow + 1)* dim + zCol]);
		neigh->push_back(new Board(gB, N, mov + 1, dType));
		swap(&gB[zRow * dim + zCol], &gB[(zRow + 1)* dim + zCol]);
	} 
	if (direction[1]) {
		// swap down
		swap(&gB[zRow * dim + zCol], &gB[(zRow - 1)* dim + zCol]);
		neigh->push_back(new Board(gB, N, mov + 1, dType));
		swap(&gB[zRow * dim + zCol], &gB[(zRow - 1)* dim + zCol]);
	} 
	if (direction[2]) {
		// swap left
		swap(&gB[zRow * dim + zCol], &gB[zRow * dim + (zCol + 1)]);
		neigh->push_back(new Board(gB, N, mov + 1, dType));
		swap(&gB[zRow * dim + zCol], &gB[zRow * dim + (zCol + 1)]);
	} 
	if (direction[3]) {
		// swap right
		swap(&gB[zRow * dim + zCol], &gB[zRow * dim + (zCol - 1)]);
		neigh->push_back(new Board(gB, N, mov + 1, dType));
		swap(&gB[zRow * dim + zCol], &gB[zRow * dim + (zCol - 1)]);
	}
}
        
unsigned int Board::get_n_moves() {
    return mov;
}        

unsigned int Board::calcHam() {
	unsigned int ham = 0;
	if (!gB) return ham;
	for(unsigned int i = 0; i < N; i++) {
		if (gB[i] != 0 && gB[i] != i + 1) ham++;
	}
	return ham;
}

unsigned int Board::hamming() {
    return dist;
}

unsigned int Board::calcMan() {
	unsigned int man = 0;
	if (!gB) return man;
	int index = 0;
	int sR = 0;
	int sC = 0;
	int aR = 0;
	int aC = 0;
	// taking advantage of index = r * dim + c formula
	for(unsigned int i = 0; i < N; i++) {
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
	if (!gB) return count;
	for(unsigned int i = 0; i < N; i++) {
		for(unsigned int j = i + 1; j < N; j++) {
			if (gB[i] > gB[j] && gB[i] != 0 && gB[j] != 0) count++;
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

void Board::print_board() {
	if (!gB) return;
    for (unsigned int i = 0 ; i < N; i ++) {
        std::cout << gB[i] << " ";
    }
}

void Board::myPrintBoard() {
	if (!gB) return;
	for(unsigned int i = 0; i < N; i++) {
		std::cout << gB[i] << ' ';
		if ((i + 1) % dim == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::string Board::boardToString() {
	std::string output = "";
	if (!gB) return output;
	for(unsigned int i = 0; i < N; i++) {
		output += std::to_string(gB[i]);
	}
	return output;
}

//-------------------------------------------------------------------------

SearchNode::SearchNode() {
	bP = nullptr;
	priority = 0;
	hash = 0;
}

SearchNode::SearchNode(Board *b, std::string *s) {
	bP = b;
	priority = calcPriority();
	hash = calcHash(s);
}

SearchNode::~SearchNode() {
	if (bP) delete bP;
} 

unsigned int SearchNode::calcPriority() {
	// doesn't matter which distance function is used
	// as in my implementation they
	// both return the distance datamember
	return bP->get_n_moves() + bP->manhattan();
}

// How Java hashes strings
unsigned int SearchNode::calcHash(std::string *s) {
	unsigned int result = 0;
	for(unsigned int i = 0; i < s->length(); i++) {
		result = (*s)[i] + (31 * result); 
	}
	return result;
}

Board* SearchNode::getBoard() {
	return bP;
}

unsigned int SearchNode::getPriority() {
	return priority;
}

unsigned int SearchNode::getHash() {
	return hash;
}
