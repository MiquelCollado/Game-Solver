#include "FiveInARow.hpp"
#include "Config.hpp"
#include "GameSolver.hpp"
#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

FiveInARow_Node::FiveInARow_Node() : NodeSquareBoard(BOARD_SIZE_X, BOARD_SIZE_Y, BOARD_DIFF){
}
FiveInARow_Node::~FiveInARow_Node(){;}

void FiveInARow_Node::init(int v[99]){
	int idx = 0;
	for(int j = 0; j< BOARD_SIZE_Y ; j++){
		for (int i = 0; i < BOARD_SIZE_X ; i++){
			board[i][j] = v[idx];
		}
	}
}
FiveInARow_Node FiveInARow_Node::dup(){
	FiveInARow_Node d;
	d.turn = turn;
//			d.h = h;
	for(int i = 0 ; i < BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
			d.board[i][j] = board[i][j];
		}
	}
	return d;
}

int FiveInARow_Node::heuristic(){
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

int FiveInARow_Node::isEndGame(){
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

vector<FiveInARow_Move> FiveInARow_Node::findMoves(){
	vector<FiveInARow_Move> moves;
	for(int i = 0 ; i < BOARD_SIZE_X ; i++){
		for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
			if(board[i][j] == 0){
				FiveInARow_Move m;
				m.x = i;
				m.y = j;
				m.player = turn;
				moves.push_back(m);
			}
		}
	}
	return(moves);
}
void FiveInARow_Node::doMove(FiveInARow_Move & move){
	board[move.x][move.y] = move.player;
	nextPlayer();
}

