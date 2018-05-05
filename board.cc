#include "board.h"

#include <iostream>
#include <cmath>

void swap(unsigned int* a, unsigned int* b) {
	unsigned int temp = *a;
	*a = *b;
	*b = temp;
}

/* Constructors and Destructors */
Board::Board() {
	dim = 0;
	N = 0;
	board = nullptr;
    dType = 0;
    dist = 0;
    mov = 0;
    priority = 0;
    inver = 0;
    zRow = 0;
    zCol = 0;
}

Board::Board(unsigned int *b, unsigned int n, unsigned int m, char type) {
	dim = sqrt(n);
	N = n;
	dType = type;
	mov = m;
	// initial values which will be redefined
	dist = 0; 
	priority = 0;
	inver = 0;
	zRow = 0;
	zCol = 0;
	board = nullptr;
	if (!n) return;
	board = new unsigned int[N];
	for(unsigned int i = 0; i < N; i++) {
		board[i] = b[i];
		if (board[i] == 0) {
			zRow = i / dim;
			zCol = abs(i - (zRow * dim));
		}
	}
	if (dType == 'm') dist = calcManhattan();
	else if (dType == 'h') dist = calcHamming();
	priority = dist + mov;
	inver = calcInversions();
}

Board::~Board() {
	if (board) {
		delete[] board;
		board = nullptr;
	}
}

/* Private Helpers */
unsigned int Board::calcManhattan() {
	unsigned int man = 0;
	if (!board) return man;
	int solvIndex = 0;
	int solvRow = 0;
	int solvCol = 0;
	int actRow = 0;
	int actCol = 0;
	for(unsigned int i = 0; i < N; i++) {
		if (board[i] == 0) continue; // ignore zero element
		solvIndex = board[i] - 1;
		solvRow = solvIndex / dim;
		solvCol = abs(solvIndex - (solvRow * dim));
		actRow = i / dim;
		actCol = abs(i - (actRow * dim));
		man += abs(solvRow - actRow) + abs(solvCol - actCol);  
	}
	return man;
}

unsigned int Board::calcHamming() {
	unsigned int ham = 0;
	if (!board) return ham;
	for(unsigned int i = 0; i < N; i++) {
		if (board[i] != 0 && board[i] != i + 1) ham++;
	}
	return ham;
}

unsigned int Board::calcInversions() {
	unsigned int inv = 0;
	if (!board) return inv;
	for(unsigned int i = 0; i < N; i++) {
		for(unsigned int j = i + 1; j < N; j++) {
			if (board[i] != 0 && board[j] != 0 && board[i] > board[j]) inv++;
		}
	}
	return inv;
}

/* Public Methods */
bool Board::is_solvable() {
	if (dim % 2 != 0 && inver % 2 == 0) return true;
	else if (dim % 2 == 0 && (inver + zRow) % 2 != 0) return true;
	return false;
}

bool Board::is_goal() {
	return (dist == 0);
}

void Board::neighbors(std::vector<Board *> *neigh, char type) {
	// r*dim+c
	if (!board) return;
	unsigned int up[N];
	unsigned int down[N];
	unsigned int left[N];
	unsigned int right[N];
	for(unsigned i = 0; i < N; i++) {
		up[i] = board[i];
		down[i] = board[i];
		left[i] = board[i];
		right[i] = board[i];
	}
	// index: 0 is up, 1 is down, 2 is left, 3 is right
	if (zRow > 0) {
		// swap zero up
		swap(&up[zRow * dim + zCol], &up[(zRow - 1) * dim + zCol]);
		neigh->push_back(new Board(up, N, mov + 1, dType));
	}
	if (zRow < dim - 1) {
		// swap zero down
		swap(&down[zRow * dim + zCol], &down[(zRow + 1) * dim + zCol]);
		neigh->push_back(new Board(down, N, mov + 1, dType));
	}
	if (zCol < dim - 1) {
		// swap zero right
		swap(&left[zRow * dim + zCol], &left[zRow * dim + (zCol + 1)]);
		neigh->push_back(new Board(left, N, mov + 1, dType));
	}
	if (zCol > 0) {
		// swap zero left
		swap(&right[zRow * dim + zCol], &right[zRow * dim + (zCol - 1)]);
		neigh->push_back(new Board(right, N, mov + 1, dType));
	}
}

unsigned int Board::get_n_moves() {
	return mov;
}

unsigned int Board::hamming() {
	return dist;
}

unsigned int Board::manhattan() {
	return dist;
}

unsigned int Board::inversions() {
	return inver;
}

void Board::print_board() {
    // the loop below assumes that `N` is the length of your array, 
    // if you have another variable name for this, please adjust 
    // the code properly
    // (for a 3 by 3 board, the value of N is 9)
    // also, if you have another name for `board` just replace it below
    for (unsigned int i = 0 ; i < N ; i ++) {
        std::cout << board[i] << " ";
    }
}

void Board::pretty_print() {
	if (!board) return;
	for(unsigned int i = 0; i < N; i++) {
		std::cout << board[i] << " ";
		if ((i + 1) % dim == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

unsigned int Board::getPriority() {
	return priority;
}

std::string Board::boardToStr() {
	std::string str = "";
	if (!board) return str;
	for(unsigned int i = 0; i < N; i++) {
		str += std::to_string(board[i]);
	}
	return str;
} 


// ---------------------------------------------------------------------------------------------------------------------------------
bool Comparator::operator() (Board *b1, Board *b2) {
	return (b1->getPriority() > b2->getPriority());
}