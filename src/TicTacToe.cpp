#include "Config.hpp"
#include "Node.hpp"
#include "Move.hpp"
#include "GameSolver.hpp"
#include "NodeEval.hpp"
#include "Persistence.hpp"

#define BOARD_SIZE_X 3
#define BOARD_SIZE_Y 3

using namespace std;

class LevelDBPersistence: public Persistence {
	public:
};

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
			return "";
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
		void print(NodeEval data){
			cout << "turn: " << turn << endl;
			cout << "heuristic: " << data.h << endl;
			for(int i = 0 ; i < BOARD_SIZE_X ; i++){
				for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
					cout << board[i][j];
				}
				cout << endl;
			}
			cout << endl;
		}
};

int main(){
	Config cfg;
	GameSolver<TicTacToe_Node, TicTacToe_Move, LevelDBPersistence> gs(cfg);
	TicTacToe_Node board;
	board.board[0][0] = 1;
	board.board[0][1] = 1;
	board.turn = 2;
	TicTacToe_Move mv = gs.findBestMove(board, 5);
}

