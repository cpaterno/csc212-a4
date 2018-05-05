#ifndef __BOARD_H__
#define __BOARD_H__

#include <string>
#include <vector>

class Board {
    private:
        // TODO
        // define your data members and private methods here
        int dim;
        unsigned int N;
        unsigned int* board;
        char dType;
        unsigned int dist;
        unsigned int mov;
        unsigned int priority;
        unsigned int inver;
        int zRow;
        int zCol;
        // private helpers
        unsigned int calcManhattan();
        unsigned int calcHamming();
        unsigned int calcInversions();


    public:
        // default constructor (for creating an empty board)
        Board();
        // full constructor
        // b: an initial board configuration
        // the board is just a sequence of numbers in row-major order (including the zero element)
        // n: number of elements in the board (including 0, for a 3x3 board n should be 9)
        // m: an initial number of moves
        // type: distance to be used 'm' for manhattan and 'b' for hamming
        Board(unsigned int *b, unsigned int n, unsigned int m, char type);
        // destructor
        ~Board();

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
        void print_board();
        // Added methods begin here
        void pretty_print();
        unsigned int getPriority();
        std::string boardToStr();
        
};

class Comparator {
    public:
       bool operator() (Board *b1, Board *b2);
};

#endif