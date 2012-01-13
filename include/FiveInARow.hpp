#include "NodeSquareBoard.hpp"
#include "Move.hpp"
#include "NodeEval.hpp"

#include <vector>

#define FIVEINAROW_BOARD_SIZE_X 10
#define FIVEINAROW_BOARD_SIZE_Y 10

using namespace std;

class FiveInARow_Move: public Move {
	public:
		int x;
		int y;
};

class FiveInARow_Node: public NodeSquareBoard {
	public:
		FiveInARow_Node();
		void init(int v[99]);
		string generateKey();
		FiveInARow_Node dup();
		int heuristic();
		int isEndGame();
		vector<FiveInARow_Move> findMoves();
		void doMove(FiveInARow_Move & move);
		void print(int depth, NodeEval data);
		void print();
};
