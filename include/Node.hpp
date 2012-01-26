#ifndef H_NODE
#define H_NODE

#include <string>
#include "NodeEval.hpp"

using namespace std;

class Node {
	public:
		int turn;
//		int h;

		virtual string generateKey(bool & reversed)=0;
//		virtual int changePlayerPiece(int p)=0;
		virtual void print(int depth, NodeEval data)=0;
		virtual void print()=0;

		Node(){
			turn = 1;
//			h = 0;
		}
		virtual ~Node(){};
		void nextPlayer(){
			turn = (turn % 2) + 1;
		}
		int nextPlayer(int t){
			return ((t % 2) + 1);
		}
};

#endif /* H_NODE */

