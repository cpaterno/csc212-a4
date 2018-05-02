#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <string>

class Board {
    private:
        // TODO
        // define your data members and private methods here
        unsigned int dim;
        unsigned int N;
        unsigned int* gB;
        char dType;
        unsigned int dist;
        unsigned int mov;
        unsigned int zRow;
        unsigned int zCol;
        unsigned int inver;
        // helpers
        unsigned int calcHam();
        unsigned int calcMan();
        unsigned int countInvers();

    public:
        // default constructor (for creating an empty board)
        Board();
        // full constructor
        // b: an initial board configuration
        // the board is just a sequence of numbers in row-major order (including the zero element)
        // n: number of elements in the board (excluding 0) so 3 by 3 is n = 8
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
        /* Added Helpers */
        unsigned int getZRow();
        unsigned int getZCol();
        void myPrintBoard();
        void print_board();
        std::string boardToString();
};

class SearchNode {
    private:
        Board *bP;
        unsigned int priority;
        unsigned int hash;
        unsigned int calcPriority();
        unsigned int calcHash(std::string *s);
    public:
        SearchNode();
        SearchNode(Board *b, std::string *s);
        ~SearchNode();
        Board* getBoard();
        unsigned int getPriority();
        unsigned int getHash();
        friend class Comparator;
};

class Comparator {
    public:
       bool operator() (SearchNode *n1, SearchNode *n2);
};

#endif