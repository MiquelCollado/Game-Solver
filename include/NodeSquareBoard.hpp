#ifndef H_NODESQUAREBOARD
#define H_NODESQUAREBOARD

#include "Node.hpp"

#define BOARD_FREE 0
#define BOARD_PLAYER_A 1
#define BOARD_PLAYER_B 2

#define BOARD_FREE(x) (x >= BOARD_FREE && x < BOARD_PLAYER_A)
#define BOARD_A(x) (x >= BOARD_PLAYER_A && x < BOARD_PLAYER_B)
#define BOARD_B(x) (x >= BOARD_PLAYER_B)

class NodeSquareBoard: public Node {
	protected:
		int X;
		int Y;
		int **board;
	public:
		virtual string generateKey()=0;

		NodeSquareBoard(int x, int y);
		~NodeSquareBoard();

		void countNumGlobal(int & playerA, int & playerB, int & free);
		int countNumInARow(int x, int y, int incX, int incY);
		int countNumFreeInARow(int x, int y, int incX, int incY);

};

#endif /* H_NODESQUAREBOARD */

