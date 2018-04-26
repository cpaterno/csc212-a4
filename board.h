#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>

class Board {
    private:
        // TODO
        // define your data members and private methods here

    public:
        // default constructor (for creating an empty board)
        Board();
        // full constructor
        // b: an initial board configuration
        // the board is just a sequence of numbers in row-major order (including the zero element)
        // n: number of elements in the board
        // m: an initial number of moves
        // type: distance to be used 'm' for manhattan and 'b' for hamming
        Board(const unsigned int *b, unsigned int n, unsigned int m, char type);
        // destructor
        ~Board();

        // verifies whether the board is solvable
        bool is_solvable();
        // verifies whether the board is a goal board
        bool is_goal();
        // returns in neigh a list of neighbors for this node
        void neighbors(std::vector<const Board *> *neigh, char type);
        // gets the number of moves made so far (up to this node)
        unsigned int get_n_moves();
        // returns the hamming distance to the goal
        unsigned int hamming();
        // returns the manhattan distance to the goal
        unsigned int manhattan();
        // counts the number of inversions on a particular board
        unsigned int inversions();
};

#endif