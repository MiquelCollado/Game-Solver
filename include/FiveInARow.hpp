#define BOARD_SIZE_X 10
#define BOARD_SIZE_Y 10
#define BOARD_DIFF 1

#include "NodeSquareBoard.hpp"
#include "Move.hpp"
#include "NodeEval.hpp"

#include <vector>

using namespace std;

class FiveInARow_Move: public Move {
	public:
		int x;
		int y;
};

class FiveInARow_Node: public NodeSquareBoard {
	public:
		FiveInARow_Node();
		~FiveInARow_Node();
		void init(unsigned char v[99]);
		FiveInARow_Node dup();
		int heuristic();
		int isEndGame();
		vector<FiveInARow_Move> findMoves();
		void doMove(FiveInARow_Move & move);
};
