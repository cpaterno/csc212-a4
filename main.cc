#include "board.h"

#include <iostream>

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board (including 0)
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve(unsigned int *b, unsigned int n, char type) {
    // TODO
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main(int argc, char **argv) {
    // reads the search type from a command line argument (either h or m)
    // reads all initial board values from the stdin
    // calls the solver passing the values of the board and the search type
}