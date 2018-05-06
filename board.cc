#include "board.h"

#include <iostream>
#include <cmath>

/*Constructors and Destructor*/

// Default Constructor
Board::Board() {
	// Initialize all datamembers to zero
	board = nullptr;
	N = 0;
	dim = 0;
	moves = 0;
	dType = 0;
	priority = 0;
	zIndex = 0;
}

// Parameterized Constructor
Board::Board(unsigned int *b, unsigned int n, unsigned int m, char type) {
	// initialize the following to the given parameter
	N = n;
	dim = sqrt(N);
	moves = m;
	dType = type;
	// guard if n is zero initialize the following 
	// to zero and return;
	if (n == 0) {
		board = nullptr;
		priority = 0;
		zIndex = 0;
		return;
	}
	// value of distance, used to calculate priority
	unsigned int dist = 0;
	// allocate memory on the heap for the board
	board = new unsigned int[N];
	// copy over values from b to board, initialize zIndex
	for(unsigned int i = 0; i < N; i++) {
		board[i] = b[i];
		if (board[i] == 0) zIndex = i;
	}
	// calculate dist based on given distance type
	if (dType == 'm') dist = manhattan();
	else if (dType == 'h') dist = hamming();
	// initialize priority as the sum of distance + moves
	priority = dist + moves;
}

// Destructor
Board::~Board() {
	// if the board exists, free its memory
	// and set board to point to nullptr
	if (board) {
		delete[] board;
		board = nullptr;
	}
}

/*Public Methods*/

// Verifies whether the board is solvable
bool Board::is_solvable() {
	// calculate inversions
	unsigned int inver = inversions();
	// calculate zRow taking advantage of the formula:
	// index = row * dimension + column
	unsigned int zRow = zIndex / dim;
	// case where odd dimension board is solvable
	if (dim % 2 != 0 && inver % 2 == 0) return true;
	// case where even dimmension board is solvable
	else if (dim % 2 == 0 && (inver + zRow) % 2 != 0) return true;
	return false;
}

// Verifies whether the board is a goal board
bool Board::is_goal() {
	// taking advantage of priority formula
	// if distance is 0, board is at its goal
	return ((priority - moves) == 0);
}

// Returns in neigh a list of neighbors for this node
void Board::neighbors(std::vector<Board *> *neigh, char type) {
	// guard if board is nullptr
	if (!board) return;
	// calculate the exact row and column of the zIndex
	// using the formula: index = row * dimension + column
	int zRow = zIndex / dim;
	int zCol = abs(zIndex - (zRow * dim));
	// pointer that will point to the updated board, upon completed move
	Board* neighborBoard = nullptr; 
	// do the following movements depending on the values of zRow and zCol
	if (zRow > 0) {
		// move zero up
		board[zIndex] = board[(zRow - 1) * dim + zCol];
		board[(zRow - 1) * dim + zCol] = 0;
		// push neighbor into vector
		neighborBoard = new Board(board, N, (moves + 1), dType);
		neigh->push_back(neighborBoard);
		// move zero back to original spot
		board[(zRow - 1) * dim + zCol] = board[zIndex];
		board[zIndex] = 0;
	}
	if (zRow < dim - 1) {
		// move zero down
		board[zIndex] = board[(zRow + 1) * dim + zCol];
		board[(zRow + 1) * dim + zCol] = 0;
		// push neighbor into vector
		neighborBoard = new Board(board, N, (moves + 1), dType);
		neigh->push_back(neighborBoard);
		// move zero back to original spot
		board[(zRow + 1) * dim + zCol] = board[zIndex];
		board[zIndex] = 0;
	}
	if (zCol > 0) {
		// move zero left
		board[zIndex] = board[zRow * dim + (zCol - 1)];
		board[zRow * dim + (zCol - 1)] = 0;
		// push neighbor into vector
		neighborBoard = new Board(board, N, (moves + 1), dType);
		neigh->push_back(neighborBoard);
		// move zero back to original spot
		board[zRow * dim + (zCol - 1)] = board[zIndex];
		board[zIndex] = 0;
	}
	if (zCol < dim - 1) {
		// move zero right
		board[zIndex] = board[zRow * dim + (zCol + 1)];
		board[zRow * dim + (zCol + 1)] = 0;
		// push neighbor into vector
		neighborBoard = new Board(board, N, (moves + 1), dType);
		neigh->push_back(neighborBoard);
		// move zero back to original spot
		board[zRow * dim + (zCol + 1)] = board[zIndex];
		board[zIndex] = 0;
	}
}

// Gets the number of moves made so far (up to this node)
unsigned int Board::get_n_moves() {
	return moves;
}

// Returns the hamming distance to the goal
unsigned int Board::hamming() {
	// guard if board is nullptr
	if (!board) return 0;
	// Hamming distance, returns the amount of elements 
	// not in their solved spot ignoring the empty element
	unsigned int ham = 0;
	for(unsigned int i = 0; i < N; i++) {
		if (board[i] != 0 && board[i] != i + 1) ham++;
	}
	return ham;
}

// Returns the manhattan distance to the goal
unsigned int Board::manhattan() {
	// guard if board is nullptr
	if (!board) return 0;
	// Manhattan distance, returns the cumulative difference between
	// each element's solved position (row, col) and its actual 
	// position (row, col), ignoring the empty element
	unsigned int man = 0;
	int solIndex = 0;
	int solRow = 0;
	int solCol = 0;
	int actRow = 0;
	int actCol = 0;
	// N casted as int to avoid unsigned int underflow
	for(int i = 0; i < int(N); i++) {
		if (board[i] == 0) continue;
		solIndex = board[i] - 1;
		solRow = solIndex / dim;
		solCol = abs(solIndex - (solRow * dim));
		actRow = i / dim;
		actCol = abs(i - (actRow * dim));
		man += abs(solRow - actRow) + abs(solCol - actCol);
	}
	return man;
}

// Counts the number of inversions on a particular board
unsigned int Board::inversions() {
	// guard if board is nullptr
	if (!board) return 0;
	unsigned int inver = 0;
	// Same inversion algorithm as a2, except modified to ignore empty element
	for(unsigned int i = 0; i < N; i++) {
		for(unsigned int j = i + 1; j < N; j++) {
			if (board[i] != 0 && board[j] != 0 && board[i] > board[j]) inver++;
		}
	}
	return inver;
}

// Prints the contents of the board
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

// Prints the contents of the board in a formatted way
void Board::pretty_print() {
	if (!board) return;
	for(unsigned int i = 0; i < N; i++) {
		std::cout << board[i] << " ";
		if ((i + 1) % dim == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Gets the board's priority
unsigned int Board::getPriority() {
	return priority;
}

// outputs a string representing the board
std::string Board::boardToStr() {
	// guard if board is nullptr
	if (!board) return "";
	std::string str = "";
	for(unsigned int i = 0; i < N; i++) {
		str += std::to_string(board[i]);
	}
	return str;
}

// ---------------------------------------------------------------------------------------------------------------------------------
// Comparator which returns true only if the first board's priority is 
// greater than the second board's priority
bool Comparator::operator() (Board *b1, Board *b2) {
	return (b1->getPriority() > b2->getPriority());
}