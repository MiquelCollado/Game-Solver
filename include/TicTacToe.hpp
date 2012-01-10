//#include "Config.hpp"
#include "NodeSquareBoard.hpp"
#include "Move.hpp"
//#include "GameSolver.hpp"
#include "NodeEval.hpp"
//#include "Persistence.hpp"

//#include "LevelDBPersistence.hpp"

#include <vector>

#define TICTACTOE_BOARD_SIZE_X 3
#define TICTACTOE_BOARD_SIZE_Y 3

using namespace std;

class TicTacToe_Move: public Move {
	public:
		int x;
		int y;
};

class TicTacToe_Node: public NodeSquareBoard {
	public:
		TicTacToe_Node();
		void init(int v[9]);
		string generateKey();
		TicTacToe_Node dup();
		int heuristic();
		int isEndGame();
		vector<TicTacToe_Move> findMoves();
		void doMove(TicTacToe_Move & move);
		void print(int depth, NodeEval data);
		void print();
};
