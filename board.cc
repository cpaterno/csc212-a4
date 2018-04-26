#include "board.h"

Board::Board() {

}       

Board::Board(const unsigned int *b, unsigned int n, unsigned int m, char type) {

}

Board::~Board() {

}


bool Board::is_solvable() {
    return false;
}

bool Board::is_goal() {
    return false;
}
        
void neighbors(std::vector<const Board *> *neigh, char type) {

}
        
unsigned int Board::get_n_moves() {
    return 0;
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

