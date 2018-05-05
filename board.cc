#include "board.h"

#include <iostream>


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