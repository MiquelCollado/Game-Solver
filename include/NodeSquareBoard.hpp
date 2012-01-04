#ifndef H_NODESQUAREBOARD
#define H_NODESQUAREBOARD

#include "Node.hpp"

#define BOARD_FREE 0

class NodeSquareBoard: public Node {
	protected:
		int X;
		int Y;
		int **board;
	public:
		virtual string generateKey()=0;

		NodeSquareBoard(int x, int y);
		~NodeSquareBoard();

		int countNumInARow(int x, int y, int incX, int incY);
		int countNumFreeInARow(int x, int y, int incX, int incY);

};

#endif /* H_NODESQUAREBOARD */

