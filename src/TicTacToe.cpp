#include "Config.hpp"
#include "Node.hpp"
#include "Move.hpp"
#include "GameSolver.hpp"
#include "NodeEval.hpp"
#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

#define BOARD_SIZE_X 3
#define BOARD_SIZE_Y 3

using namespace std;

class TicTacToe_Move: public Move {
	public:
		int x;
		int y;
};

class TicTacToe_Node: public Node {
	public:
		int board[3][3];

		TicTacToe_Node(){
			for(int i = 0 ; i < BOARD_SIZE_X ; i++){
				for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
					board[i][j] = 0;
				}
			}
		}
		string generateKey(){
			vector<string> keys;
			stringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8;//create a stringstream

			ss1 << turn;//add number to the stream
			ss2 << turn;//add number to the stream
			ss3 << turn;//add number to the stream
			ss4 << turn;//add number to the stream
			ss5 << turn;//add number to the stream
			ss6 << turn;//add number to the stream
			ss7 << turn;//add number to the stream
			ss8 << turn;//add number to the stream
			for(int i = 0 ; i < BOARD_SIZE_X ; i++){
				for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
					ss1 << board[i]						[j];					//Normal
					ss2 << board[BOARD_SIZE_X - i - 1]	[j];					//Flip X
					ss3 << board[i]						[BOARD_SIZE_Y - j - 1];	//Flip Y
					ss4 << board[BOARD_SIZE_X - i - 1]	[BOARD_SIZE_Y - j - 1]; //Flip XY
					ss5 << board[j]						[i];					//Mirror
					ss6 << board[BOARD_SIZE_Y - j - 1]	[i];					//Mirror Flip X
					ss7 << board[j]						[BOARD_SIZE_X - i - 1];	//Mirror Flip Y
					ss8 << board[BOARD_SIZE_Y - j - 1]	[BOARD_SIZE_X - i - 1]; //Mirror Flip XY
				}
			}
			keys.push_back(ss1.str());
			keys.push_back(ss2.str());
			keys.push_back(ss3.str());
			keys.push_back(ss4.str());
			keys.push_back(ss5.str());
			keys.push_back(ss6.str());
			keys.push_back(ss7.str());
			keys.push_back(ss8.str());
			// using function as comp
//			sort (keys.begin(), keys.end());
//			sort (keys.begin(), keys.end(), myfunction);

			return keys[0];//return a string with the contents of the stream
		}
		TicTacToe_Node dup(){
			TicTacToe_Node d;
			d.turn = turn;
//			d.h = h;
			for(int i = 0 ; i < BOARD_SIZE_X ; i++){
				for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
					d.board[i][j] = board[i][j];
				}
			}
			return d;
		}

		int heuristic(){
			int h = 0;

			int end = isEndGame();
			if(end == GAME_WIN_FIRST){
				h = LONG_MAX;
			} else if(end == GAME_WIN_SECOND){
				h = LONG_MIN;
			} else {
				for(int i = 0 ; i < BOARD_SIZE_X ; i++){
					for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
						if(board[i][j] == 1)
							h++;
						else if(board[i][j] == 2)
							h--;
					}
				}
			}
//			cout << "end: " << end << endl;
//			print();
			return h;
		}

		int isEndGame(){
			int ret = GAME_PLAYING;
			int zero = 0;

			if(board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2]){ // Diagonal
				ret = board[0][0];
			}else if(board[0][2] != 0 && board[0][2] == board[1][1] && board[0][2] == board[2][0]){ // Diagonal
				ret = board[0][2];
			}else{
				for(int i = 0 ; i < BOARD_SIZE_X ; i++){
					if(board[i][0] != 0 && board[i][0] == board[i][1] && board[i][0] == board[i][2]){ //Fila
						ret = board[i][0];
						break;
					}
					if(board[0][i] != 0 && board[0][i] == board[1][i] && board[0][i] == board[2][i]){ //Columna
						ret = board[0][i];
						break;
					}
					for(int j = 0 ; j < BOARD_SIZE_Y ; j++){ // Cuenta los 0's
						if(board[i][j] == 0)
							zero++;
					}
				}
			}
			if(ret == GAME_PLAYING && zero == 0) // Si no gana nadie y no quedan espacios libres
				ret = GAME_DRAW;
			return ret;
		}

		vector<TicTacToe_Move> findMoves(){
			vector<TicTacToe_Move> moves;
			for(int i = 0 ; i < BOARD_SIZE_X ; i++){
				for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
					if(board[i][j] == 0){
						TicTacToe_Move m;
						m.x = i;
						m.y = j;
						m.player = turn;
						moves.push_back(m);
					}
				}
			}
			return(moves);
		}
		void doMove(TicTacToe_Move & move){
			board[move.x][move.y] = move.player;
			nextPlayer();
		}
		void print(int depth, NodeEval data){
			string pre(12 - depth,  ' ');
			cout << pre << "turn: " << turn << endl;
			cout << pre << "heuristic: " << data.h << endl;
			cout << pre << "distanceEnd: " << data.distanceEnd << endl;
			cout << pre << "depth: " << data.depth << endl;
			for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
				cout << pre;
				for(int i = 0 ; i < BOARD_SIZE_X ; i++){
					cout << board[i][j];
				}
				cout << endl;
			}
			cout << endl;
		}
		void print(){
			cout << "turn: " << turn << endl;
			for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
				for(int i = 0 ; i < BOARD_SIZE_X ; i++){
					cout << board[i][j];
				}
				cout << endl;
			}
			cout << endl;
		}
};

int main(){
	Config cfg;
	cfg.Algorithm = ALGORITHM_MINMAX;
	cfg.PersistenceUse = true;
	cfg.PersistenceMinDepthToSave = 9;
	cfg.PersistenceName = "DB_TicTacToe";
	cfg.TimeoutUse = false;
	cfg.TimeoutSeconds = 0;

	GameSolver<TicTacToe_Node, TicTacToe_Move, LevelDBPersistence> gs(cfg);
	TicTacToe_Node board;
	board.board[0][0] = 1; board.board[1][0] = 1; board.board[2][0] = 0;
	board.board[0][1] = 0; board.board[1][1] = 2; board.board[2][1] = 0;
	board.board[0][2] = 0; board.board[1][2] = 0; board.board[2][2] = 0;
	board.turn = 1;
	TicTacToe_Move mv = gs.findBestMove(board, 10);
	board.doMove(mv);
	board.print();
	
}

