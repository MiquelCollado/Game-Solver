#define BOARD_SIZE_X 3
#define BOARD_SIZE_Y 3
#define BOARD_DIFF 1
/*
#define BOARD_FREE 0		//0
#define BOARD_PLAYER_A 1	//1
#define BOARD_PLAYER_B 2	//11

#define BOARD_FREE(x) (x >= BOARD_FREE && x < BOARD_PLAYER_A)
#define BOARD_A(x) (x >= BOARD_PLAYER_A && x < BOARD_PLAYER_B)
#define BOARD_B(x) (x >= BOARD_PLAYER_B)
#define CHANGE_PLAYER(x) ( (x>=BOARD_PLAYER_B) ? (x - (BOARD_PLAYER_B - BOARD_PLAYER_A)): (x + (BOARD_PLAYER_B - BOARD_PLAYER_A)) )
*/
//#include "Config.hpp"
#include "NodeSquareBoard.hpp"
#include "Move.hpp"
//#include "GameSolver.hpp"
#include "NodeEval.hpp"
//#include "Persistence.hpp"

//#include "LevelDBPersistence.hpp"

#include <vector>

using namespace std;

class TicTacToe_Move: public Move {
	public:
		int x;
		int y;
};

class TicTacToe_Node: public NodeSquareBoard {
	public:
		TicTacToe_Node();
		~TicTacToe_Node();
		void init(int v[9]);

		TicTacToe_Node dup();
		int heuristic();
		int isEndGame();
		vector<TicTacToe_Move> findMoves();
		void doMove(TicTacToe_Move & move);
};
