#include "board.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

// How Java hashes strings
unsigned int calcHash(std::string *s) {
    unsigned int result = 0;
    for(unsigned int i = 0; i < s->length(); i++) {
        result = (*s)[i] + (31 * result);
    }
    return result;
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
    root.myPrintBoard();
    root.neighbors(&neighbors, type);
    for(unsigned int i = 0; i < neighbors.size(); i++) {
        neighbors[i]->myPrintBoard();
        delete neighbors[i];
    }
    std::cout << std::endl;
    std::cout << root.boardToString() << std::endl;
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
    std::vector<Board*> neigh;
    Board root = Board(b, n, 0, type);
    std::string boardStr = root.boardToString();
    unsigned int hash = calcHash(&boardStr);
    std::priority_queue<Board*, std::vector<Board*>, Comparator> boardQ;
    std::unordered_set<unsigned int> visited;
    boardQ.push(&root);
    visited.insert(hash);
    Board* goalBoard = nullptr;
    while(!boardQ.empty()) {
        goalBoard = boardQ.top();
        if (goalBoard->is_goal()) {
            std::cout <<"Number of moves: " << goalBoard->get_n_moves() << std::endl;
            boardQ.pop();
            break;
        }
        if(!goalBoard->is_solvable()) {
            std::cout << "Unsolvable board" << std::endl;
            boardQ.pop();
            break;
        }
        boardQ.pop();
        goalBoard->neighbors(&neigh, type);
        for(Board* i : neigh) {
            boardStr = i->boardToString();
            hash = calcHash(&boardStr);
            if (visited.find(hash) == visited.end()) {
                boardQ.push(i);
                visited.insert(hash);
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
    solve(b, len, type);
    //testMethods(b, len, type);
    //nMovesLoop(b, len, type);
    return 0;
}