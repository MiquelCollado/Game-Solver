#ifndef H_NODE
#define H_NODE

class Node {
	public:
		int turn;
//		int h;

		virtual string generateKey();

		Node(){
			turn = 1;
//			h = 0;
		}
		void nextPlayer(){
			turn = (turn % 2) + 1;
		}
};

#endif /* H_NODE */
