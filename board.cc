#include "board.h"

#include <iostream>
#include <cmath>

void copyArray(unsigned int* original, unsigned int* copy, unsigned int N) {
	for(unsigned int i = 0; i < N; i++) copy[i] = original[i];
}


Board::Board() {
	
}

/*Constructors and Destructor*/

// Parameterized Constructor
Board::Board(unsigned int *b, unsigned int n, unsigned int m, char type) {
	// update the following to the given parameter
	N = n;
	dim = sqrt(N);
	moves = m;
	dType = type;
	// value of distance, used to calculate priority
	unsigned int dist = 0;
	// have board point to an array representing a board on the stack
	if (n == 0) return;
	board = b;
	// update zIndex
	for(unsigned int i = 0; i < N; i++) {
		if (board[i] == 0) zIndex = i;
	}
	// calculate dist based on given distance type
	if (dType == 'm') dist = manhattan();
	else if (dType == 'h') dist = hamming();
	// update priority as the sum of distance + moves
	priority = dist + moves;
}

Board::~Board() {
	// nothing to delete
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
	// if distance (distance can be calculated as priority - moves because
	// priority is moves + distance) is 0, board is at its goal
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
	unsigned int* upBoard = nullptr;
	unsigned int* downBoard = nullptr;
	unsigned int* leftBoard = nullptr;
	unsigned int* rightBoard = nullptr; 
	// do the following movements depending on the values of zRow and zCol
	if (zRow > 0 && zRow < dim) {
		// move zero up
		upBoard = new unsigned int[N];
		copyArray(board, upBoard, N);
		upBoard[zIndex] = upBoard[(zRow - 1) * dim + zCol];
		upBoard[(zRow - 1) * dim + zCol] = 0;
		// push neighbor into vector
		neigh->push_back(new Board(upBoard, N, (moves + 1), dType));
	}
	if (zRow > -1 && zRow < dim - 1) {
		// move zero down
		downBoard = new unsigned int[N];
		copyArray(board, downBoard, N);
		downBoard[zIndex] = downBoard[(zRow + 1) * dim + zCol];
		downBoard[(zRow + 1) * dim + zCol] = 0;
		// push neighbor into vector
		neigh->push_back(new Board(downBoard, N, (moves + 1), dType));
	}
	if (zCol > 0 && zCol < dim) {
		// move zero left
		leftBoard = new unsigned int[N];
		copyArray(board, leftBoard, N);
		leftBoard[zIndex] = leftBoard[zRow * dim + (zCol - 1)];
		leftBoard[zRow * dim + (zCol - 1)] = 0;
		// push neighbor into vector
		neigh->push_back(new Board(leftBoard, N, (moves + 1), dType));
	}
	if (zCol > -1 && zCol < dim - 1) {
		// move zero right
		rightBoard = new unsigned int[N];
		copyArray(board, rightBoard, N);
		rightBoard[zIndex] = rightBoard[zRow * dim + (zCol + 1)];
		rightBoard[zRow * dim + (zCol + 1)] = 0;
		// push neighbor into vector
		neigh->push_back(new Board(rightBoard, N, (moves + 1), dType));
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
	int solIndex, solRow, solCol, actRow, actCol;
	solIndex = solRow = solCol = actRow = actCol = 0;
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