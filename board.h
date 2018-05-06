#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <string>

class Board {
    private:
        // array on the heap which represents the board
        unsigned int* board = nullptr;
        // the number of elements in a board
        unsigned int N = 0;
        // the dimension of each side of the board
        int dim = 0;
        // the amount of moves made to get to this board
        unsigned int moves;
        // distance type
        char dType = 0;
        // priority of the board used for A* search
        unsigned int priority = 0;
        // index of the empty space in the board (used in calculations)
        int zIndex = 0;


    public:
        // default constructor (for creating an empty board)
        Board() { }
        // full constructor
        // b: an initial board configuration
        // the board is just a sequence of numbers in row-major order (including the zero element)
        // n: number of elements in the board (including 0, for a 3x3 board n should be 9)
        // m: an initial number of moves
        // type: distance to be used 'm' for manhattan and 'h' for hamming
        Board(unsigned int *b, unsigned int n, unsigned int m, char type);
        // destructor
        ~Board() { }

        // verifies whether the board is solvable
        bool is_solvable();
        // verifies whether the board is a goal board
        bool is_goal();
        // returns in neigh a list of neighbors for this node
        void neighbors(std::vector<Board *> *neigh, char type);
        // gets the number of moves made so far (up to this node)
        unsigned int get_n_moves();
        // returns the hamming distance to the goal
        unsigned int hamming();
        // returns the manhattan distance to the goal
        unsigned int manhattan();
        // counts the number of inversions on a particular board
        unsigned int inversions();
        // prints the contents of the board
        void print_board();
        // Additional Methods
        // prints the contents of the board in a formatted way
        void pretty_print();
        // gets the board's priority
        unsigned int getPriority();
        // outputs a string representing the board
        std::string boardToStr();
};

// Comparator class passed to the STL priority queue
class Comparator {
    public:
       bool operator() (Board *b1, Board *b2) {
            return (b1->getPriority() > b2->getPriority());
       }
};

#endif