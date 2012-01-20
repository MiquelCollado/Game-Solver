#ifndef H_NODESQUAREBOARD
#define H_NODESQUAREBOARD

#include "Node.hpp"

class NodeSquareBoard: public Node {
	protected:
		int X;
		int Y;
		int PieceDiff;
		int **board;
	public:
		NodeSquareBoard(int x, int y, int pieceDiff);
		~NodeSquareBoard();

		int changePlayerPiece(int piece);
		string generateKey(bool & reversed);
		void print(int depth, NodeEval data);
		void print();
		void countNumGlobal(int & playerA, int & playerB, int & free);
		int countNumInARow(int x, int y, int incX, int incY);
		int countNumFreeInARow(int x, int y, int incX, int incY, int same);

};

#endif /* H_NODESQUAREBOARD */

