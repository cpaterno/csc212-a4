#include "board.h"
#include <iostream>
#include <cmath> 
#include <vector>
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
    bool firstNum = true;
    std::vector<unsigned int> v;
    int num = 0;
    int nPuzzle = 0;
    // reads all initial board values from the stdin
    while(std::cin >> num) {
    	if (firstNum) {
    		firstNum = false;
    		nPuzzle = pow(num, 2) - 1;
    	} else {
    		v.push_back(num);
    	}
    }
    // calls the solver passing the values of the board and the search type
    const unsigned int *b = &v[0];
    solve(b, nPuzzle, type);
    return 0;
}