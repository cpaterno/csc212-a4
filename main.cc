#include "board.h"
#include <iostream>
#include <cmath> 
#include <vector>
#include <queue>

void testMethods(const unsigned int *b, unsigned int n, char type) {
	Board* root = new Board(b, n, 0, type);
	std::vector<Board*> neighbors;
    std::cout << std::boolalpha << root->is_solvable() << std::endl;
    std::cout << std::boolalpha << root->is_goal() << std::endl;
    std::cout << root->get_n_moves() << std::endl;
    std::cout << root->inversions() << std::endl;
    std::cout << root->manhattan() << std::endl;
} 

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve(const unsigned int *b, unsigned int n, char type) { 
    Board* root = new Board(b, n, 0, type);
    std::vector<Board*> neighbors;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main(int argc, char **argv) {
    // reads the search type from a command line argument (either h or m)
    if (argc != 2) return 1;
    char type = argv[1][0];
    if (argv[1][0] == 'h') type = 'b'; 
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
    //solve(b, nPuzzle, type);
    testMethods(b, nPuzzle, type);
    return 0;
}