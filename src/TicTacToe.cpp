#include "TicTacToe.hpp"
#include "Config.hpp"
//#include "NodeSquareBoard.hpp"
//#include "Move.hpp"
#include "GameSolver.hpp"
//#include "NodeEval.hpp"
#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"


TicTacToe_Node::TicTacToe_Node() : NodeSquareBoard(TICTACTOE_BOARD_SIZE_X, TICTACTOE_BOARD_SIZE_Y){
	for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
			board[i][j] = 0;
		}
	}
}
void TicTacToe_Node::init(int v[9]){
	board[0][0] = v[0]; board[1][0] = v[1]; board[2][0] = v[2];
	board[0][1] = v[3]; board[1][1] = v[4]; board[2][1] = v[5];
	board[0][2] = v[6]; board[1][2] = v[7]; board[2][2] = v[8];
}
string TicTacToe_Node::generateKey(){
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
	for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
			ss1 << board[i]					[j];					//Normal
			ss2 << board[TICTACTOE_BOARD_SIZE_X - i - 1]	[j];					//Flip X
			ss3 << board[i]					[TICTACTOE_BOARD_SIZE_Y - j - 1];	//Flip Y
			ss4 << board[TICTACTOE_BOARD_SIZE_X - i - 1]	[TICTACTOE_BOARD_SIZE_Y - j - 1]; 	//Flip XY
			ss5 << board[j]					[i];					//Mirror
			ss6 << board[TICTACTOE_BOARD_SIZE_Y - j - 1]	[i];					//Mirror Flip X
			ss7 << board[j]					[TICTACTOE_BOARD_SIZE_X - i - 1];	//Mirror Flip Y
			ss8 << board[TICTACTOE_BOARD_SIZE_Y - j - 1]	[TICTACTOE_BOARD_SIZE_X - i - 1]; 	//Mirror Flip XY
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
TicTacToe_Node TicTacToe_Node::dup(){
	TicTacToe_Node d;
	d.turn = turn;
//			d.h = h;
	for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
			d.board[i][j] = board[i][j];
		}
	}
	return d;
}

int TicTacToe_Node::heuristic(){
	int h = 0;

	int end = isEndGame();
	if(end == GAME_WIN_FIRST){
		h = LONG_MAX;
	} else if(end == GAME_WIN_SECOND){
		h = LONG_MIN;
	} else {
		for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
			for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
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

int TicTacToe_Node::isEndGame(){
	int ret = GAME_PLAYING;
	int zero = 0;

	if(board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2]){ // Diagonal
		ret = board[0][0];
	}else if(board[0][2] != 0 && board[0][2] == board[1][1] && board[0][2] == board[2][0]){ // Diagonal
		ret = board[0][2];
	}else{
		for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
			if(board[i][0] != 0 && board[i][0] == board[i][1] && board[i][0] == board[i][2]){ //Fila
				ret = board[i][0];
				break;
			}
			if(board[0][i] != 0 && board[0][i] == board[1][i] && board[0][i] == board[2][i]){ //Columna
				ret = board[0][i];
				break;
			}
			for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){ // Cuenta los 0's
				if(board[i][j] == 0)
					zero++;
			}
		}
	}
	if(ret == GAME_PLAYING && zero == 0) // Si no gana nadie y no quedan espacios libres
		ret = GAME_DRAW;
	return ret;
}

vector<TicTacToe_Move> TicTacToe_Node::findMoves(){
	vector<TicTacToe_Move> moves;
	for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
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
void TicTacToe_Node::doMove(TicTacToe_Move & move){
	board[move.x][move.y] = move.player;
	nextPlayer();
}
void TicTacToe_Node::print(int depth, NodeEval data){
	string pre(12 - depth,  ' ');
	cout << pre << "turn: " << turn << endl;
	cout << pre << "heuristic: " << data.h << endl;
	cout << pre << "distanceEnd: " << data.distanceEnd << endl;
	cout << pre << "depth: " << data.depth << endl;
	for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
		cout << pre;
		for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void TicTacToe_Node::print(){
	cout << "turn: " << turn << endl;
	for(int j = 0 ; j < TICTACTOE_BOARD_SIZE_Y ; j++){
		for(int i = 0 ; i < TICTACTOE_BOARD_SIZE_X ; i++){
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

