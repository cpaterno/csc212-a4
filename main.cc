#include "board.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath> 

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve(const unsigned int *b, unsigned int n, char type) {
    // TODO
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main(int argc, char **argv) {
    // reads the search type from a command line argument (either h or m)
    if (argc != 2) return 1;
    char type = argv[1][0];
    bool firstNum = false;
    int index = 0;
    int num = 0;
    int len = 0;
    // reads all initial board values from the stdin
    // calls the solver passing the values of the board and the search type
}