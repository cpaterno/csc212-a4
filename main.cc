#include "board.h"
#include <iostream>
#include <vector>
#include <queue>

void nMovesLoop(unsigned int *b, unsigned int n, char type) {
    for(int i = 0; i < 1000000; i++) {
        Board root = Board(b, n, i, type);
        std::cout << root.get_n_moves() << std::endl;
    }
}

void testMethods(unsigned int *b, unsigned int n, char type) {
	Board root = Board(b, n, 0, type);
	std::vector<Board*> neighbors;
    std::cout << std::boolalpha << "The board is solvable -> " << root.is_solvable() << std::endl;
    std::cout << std::boolalpha << "The board is goal -> " << root.is_goal() << std::endl;
    std::cout << root.get_n_moves() << " moves were made " << std::endl;
    std::cout << "The board has " << root.inversions() << " inversions." << std::endl;
    std::cout << "The board's distance is " << root.manhattan() << std::endl;
    std::cout << "The board's zero row is " << root.getZRow() << std::endl;
    std::cout << "The board's zero col is " << root.getZCol() << std::endl;
    root.printBoard();
    root.neighbors(&neighbors, type);
    for(unsigned int i = 0; i < neighbors.size(); i++) {
        neighbors[i]->printBoard();
        delete neighbors[i];
    }
    std::cout << std::endl;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve(unsigned int *b, unsigned int n, char type) {
    //Board* root = new Board(b, n, 0, type);
    //std::vector<Board*> neighbors;
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
    int len = 0;
    // reads all initial board values from the stdin
    while(std::cin >> num) {
    	if (firstNum) {
    		firstNum = false;
    		len = num * num;
    	} else {
    		v.push_back(num);
    	}
    }
    // calls the solver passing the values of the board and the search type
    unsigned int *b = &v[0];
    //solve(b, len, type);
    //testMethods(b, len, type);
    nMovesLoop(b, len, type);
    return 0;
}