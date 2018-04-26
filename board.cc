#include "board.h"

Board::Board() {
	dim = 0; // calculated
	gB = nullptr;
	dType = 0;
	dist = 0;
	mov = 0;
	zRow = 0;
}       

Board::Board(const unsigned int *b, unsigned int n, unsigned int m, char type) {

}

Board::~Board() {

}


bool Board::is_solvable() {
	// follow formula
    return false;
}

bool Board::is_goal() {
	// distance is 0 -> true
    return false;
}
        
void neighbors(std::vector<const Board *> *neigh, char type) {

}
        
unsigned int Board::get_n_moves() {
    return mov;
}        

unsigned int Board::hamming() {
    return 0;
}

unsigned int Board::manhattan() {
    return 0;
}

unsigned int Board::inversions() {
    return 0;
}

