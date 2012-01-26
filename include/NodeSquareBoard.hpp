#ifndef H_NODESQUAREBOARD
#define H_NODESQUAREBOARD

#include "Node.hpp"

class NodeSquareBoard: public Node {
	private:
/*
		int *changePlayer;
		int changePlayerPiece(int piece){
			if(changePlayer == null){
				changePlayer = new int [pieceDiff*2 + 1];
				changePlayer[0] = 0;
				for(int i=1; i<=pieceDiff; i++)
					changePlayer[i] = changePlayer[i + pieceDiff];
				for(int i=pieceDiff+1; i<=pieceDiff*2; i++)
					changePlayer[i] = changePlayer[i - pieceDiff];
			}
			return changePlayer[piece];
		}
*/
		inline unsigned char changePlayerPiece(unsigned char piece){
			unsigned char changes[] = {0,2,1};
			return changes[piece];
/*
			if(piece == 0)
				return 0;
			else if(piece > PieceDiff)
				return piece - PieceDiff;
			else
				return piece + PieceDiff;
*/
		}

	protected:
		int X;
		int Y;
		unsigned char PieceDiff;
		unsigned char **board;
	public:
		NodeSquareBoard(int x, int y, unsigned char pieceDiff);
		~NodeSquareBoard();

		string generateKey(bool & reversed);
		void print(int depth, NodeEval data);
		void print();
		void countNumGlobal(int & playerA, int & playerB, int & free);
		int countNumInARow(int x, int y, int incX, int incY);
		int countNumFreeInARow(int x, int y, int incX, int incY, unsigned char same);

};

#endif /* H_NODESQUAREBOARD */

