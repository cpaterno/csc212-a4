#include "board.h"

#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

// function for testing my board methods
void testMethods(unsigned int *b, unsigned int n, char type) {
    Board root = Board(b, n, 0, type);
    std::vector<Board*> neighbors;
    std::cout << std::boolalpha << "The board is solvable -> " << root.is_solvable() << std::endl;
    std::cout << std::boolalpha << "The board is goal -> " << root.is_goal() << std::endl;
    std::cout << root.get_n_moves() << " moves were made " << std::endl;
    std::cout << "The board has " << root.inversions() << " inversions." << std::endl;
    std::cout << "The board's distance is " << (root.getPriority() - root.get_n_moves()) << std::endl;
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
    // initialize first board and a string representation of boards
    Board* root = new Board(b, n, 0, type);
    std::string boardStr = root->boardToStr();
    // pointer to min value in minheap priority queue
    Board* goalBoard = nullptr;
    std::vector<Board*> memCleanup;
    // initialize minheap priority queue and hash table
    std::priority_queue<Board*, std::vector<Board*>, Comparator> boardQ;
    std::unordered_set<std::string> visited;
    // add the first board and its string representation into 
    // the correct data structures
    boardQ.emplace(root);
    visited.insert(boardStr);
    // while the queue is not empty or base cases not hit
    // do A* search
    while(!boardQ.empty()) {
        // get the board with the lowest priority 
        // and remove it from the queue
        goalBoard = boardQ.top();
        boardQ.pop();
        // base case 1: board is solved
        if (goalBoard->is_goal()) {
            std::cout << "Number of moves: " << goalBoard->get_n_moves();
            memCleanup.push_back(goalBoard);
            break;
        }
        // base case 2: board is unsolvable
        if (!goalBoard->is_solvable()) {
            std::cout << "Unsolvable board";
            memCleanup.push_back(goalBoard);
            break; 
        }
        // create a vector of neighbors
        std::vector<Board*> neigh;
        goalBoard->neighbors(&neigh, type);
        memCleanup.push_back(goalBoard);
        // check if each neighbor has never been seen before
        // and if not add it to the queue and hash table 
        for(unsigned int i = 0; i < neigh.size(); i++) {
            boardStr = neigh[i]->boardToStr();
            // if the string representation of the board is not
            // in the hash table, then we can add the board to the queue
            // and its string representation to the hash table
            if (visited.find(boardStr) == visited.end()) {
                boardQ.emplace(neigh[i]);
                visited.insert(boardStr);
            } else memCleanup.push_back(goalBoard);
        }
    }
    while(!boardQ.empty()) {
        goalBoard = boardQ.top();
        boardQ.pop();
        memCleanup.push_back(goalBoard);
    }
    for(Board* d : memCleanup) {
        delete d;
    }
}

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
// it all starts here
// -----------------------------------------------------------------------
int main(int argc, char **argv) {
    if (argc != 2) return 1;
    // reads the search type from a command line argument (either h or m)
    char type = argv[1][0];
    unsigned int dim = 0;
    std::cin >> dim;
    unsigned int n = dim * dim;
    unsigned int input[n];
    // reads all initial board values from the stdin
    for(unsigned int i = 0; i < n; i++) {
        std::cin >> input[i];
    }
    // calls the solver passing the values of the board and the search type
    solve(input, n, type);
    //testMethods(input, n, type);
    return 0;
}