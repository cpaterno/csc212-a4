#include "board.h"

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>


void testMethods(unsigned int *b, unsigned int n, char type) {
	Board root = Board(b, n, 0, type);
	std::vector<Board*> neighbors;
    std::cout << std::boolalpha << "The board is solvable -> " << root.is_solvable() << std::endl;
    std::cout << std::boolalpha << "The board is goal -> " << root.is_goal() << std::endl;
    std::cout << root.get_n_moves() << " moves were made " << std::endl;
    std::cout << "The board has " << root.inversions() << " inversions." << std::endl;
    std::cout << "The board's distance is " << root.manhattan() << std::endl;
    root.pretty_print();
    root.neighbors(&neighbors, type);
    for(unsigned int i = 0; i < neighbors.size(); i++) {
        neighbors[i]->pretty_print();
        delete neighbors[i];
    }
    std::cout << root.boardToStr() << std::endl;
    std::cout << std::endl;
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// this is the main solver
// -----------------------------------------------------------------------
// b: an initial board configuration
// the board is just a sequence of numbers in row-major order (including the zero element)
// n: number of elements in the board (including 0)
// type: distance to be used 'm' for manhattan and 'b' for hamming
void solve(unsigned int *b, unsigned int n, char type) {
    Board root = Board(b, n, 0, type);
    std::vector<Board*> neigh;
    std::string boardStr = root.boardToStr();
    std::priority_queue<Board*, std::vector<Board*>, Comparator> boardQ;
    std::unordered_set<std::string> visited;
    boardQ.push(&root);
    visited.insert(boardStr);
    Board *goalBoard = nullptr;
    while(!boardQ.empty()) {
        goalBoard = boardQ.top();
        boardQ.pop();
        if (goalBoard->is_goal()) {
            std::cout <<"Number of moves: " << goalBoard->get_n_moves();
            break;
        }
        if(!goalBoard->is_solvable()) {
            std::cout << "Unsolvable board";
            break;
        }
        goalBoard->neighbors(&neigh, type);
        for(unsigned int i = 0; i < neigh.size(); i++) {
            boardStr = neigh[i]->boardToStr();
            if (visited.find(boardStr) == visited.end()) {
                boardQ.push(neigh[i]);
                visited.insert(boardStr);
            }
        }
        neigh.clear();
    }
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main(int argc, char **argv) {
    // reads the search type from a command line argument (either h or m)
    char type = argv[1][0];
    unsigned int dimension = 0;
    unsigned int num = 0;
    std::cin >> dimension;
    unsigned int len = dimension * dimension;
    unsigned int puzzle[len];
    // reads all initial board values from the stdin
    for(unsigned int i = 0; i < len; i++) {
    	std::cin >> num;
    	puzzle[i] = num;
    }
    // calls the solver passing the values of the board and the search type
    //solve(puzzle, len, type);
    testMethods(puzzle, len, type);
    return 0;
}