#include "FiveInARow.hpp"
#include "Config.hpp"
#include "GameSolver.hpp"
#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

FiveInARow_Node::FiveInARow_Node() : NodeSquareBoard(BOARD_SIZE_X, BOARD_SIZE_Y, (unsigned char)BOARD_DIFF){
}
FiveInARow_Node::~FiveInARow_Node(){;}

void FiveInARow_Node::init(unsigned char v[99]){
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
	int playerA=0, playerB=0, free=0;

	countNumGlobal(playerA, playerB, free);
	int end = isEndGame();
	if(end == GAME_WIN_FIRST){
		h = LONG_MAX;
	} else if(end == GAME_WIN_SECOND){
		h = LONG_MIN;
	} else if(end == GAME_DRAW){
		h = 0;
	} else {
		h = playerA - playerB;
//cout << "H Diff playerA: " << playerA << " playerB: " << playerB << " free: " << free << endl;
		for(int i = 0 ; i < BOARD_SIZE_X ; i++){
			for(int j = 0 ; j < BOARD_SIZE_Y ; j++){
				int countH, countHFreeL, countHFreeR, countV, countVFreeU, countVFreeD;
				int countD1, countD1FreeL, countD1FreeR, countD2, countD2FreeL, countD2FreeR;
				int mult;
				if(board[i][j] != 0){
					if(board[i][j] == 1)
						mult = 1;
					else
						mult = -1;

					countH = countNumInARow(i, j, 1, 0);
					countHFreeL = countNumFreeInARow(i, j, 1, 0, board[i][j]);
					countHFreeR = countNumFreeInARow(i, j, -1, 0, board[i][j]);
					if(countH + countHFreeL >= 5 && countH + countHFreeR >= 5)
						h = h + (4 * mult);//The factor countH is implicit because it is evaluated countH times
					else if(countH + countHFreeL >= 5 || countH + countHFreeR >= 5)
						h = h + (2 * mult);
					else if(countH + countHFreeL + countHFreeR >= 5)
						h = h + (mult);

					countV = countNumInARow(i, j, 0, 1);
					countVFreeU = countNumFreeInARow(i, j, 0, 1, board[i][j]);
					countVFreeD = countNumFreeInARow(i, j, 0, -1, board[i][j]);
					if(countV + countVFreeU >= 5 && countV + countVFreeD >= 5)
						h = h + (4 * mult);
					else if(countV + countVFreeU >= 5 || countV + countVFreeD >= 5)
						h = h + (2 * mult);
					else if(countV + countVFreeU + countVFreeD >= 5)
						h = h + (mult);

					countD1 = countNumInARow(i, j, 1, 1);
					countD1FreeL = countNumFreeInARow(i, j, 1, 1, board[i][j]);
					countD1FreeR = countNumFreeInARow(i, j, -1, -1, board[i][j]);
					if(countD1 + countD1FreeL >= 5 && countD1 + countD1FreeR >= 5)
						h = h + (4 * mult);
					else if(countD1 + countD1FreeL >= 5 || countD1 + countD1FreeR >= 5)
						h = h + (2 * mult);
					else if(countD1 + countD1FreeL + countD1FreeR >= 5)
						h = h + (mult);

					countD2 = countNumInARow(i, j, -1, 1);
					countD2FreeL = countNumFreeInARow(i, j, -1, 1, board[i][j]);
					countD2FreeR = countNumFreeInARow(i, j, 1, -1, board[i][j]);
					if(countD2 + countD2FreeL >= 5 && countD2 + countD2FreeR >= 5)
						h = h + (4 * mult);
					else if(countD2 + countD2FreeL >= 5 || countD2 + countD2FreeR >= 5)
						h = h + (2 * mult);
					else if(countD2 + countD2FreeL + countD2FreeR >= 5)
						h = h + (mult);
//cout << "H Update (" << i << "," << j << "): " << h << endl;
				}
			}
		}
	}
	return h;
}

int FiveInARow_Node::isEndGame(){
	int ret = GAME_PLAYING;
	int zero = 0;
	int i, j, k;
	int countH, countV, countD1, countD2;
	for(i = 0 ; i < BOARD_SIZE_X ; i++){
		for(j = 0 ; j < BOARD_SIZE_Y; j++){
			countH = 1;
			countV = 1;
			countD1 = 1;
			countD2 = 1;
			if(board[i][j] != 0){
				for(k = 1 ; k < 5 ; k++){
					if(j+k < BOARD_SIZE_Y){
						if(board[i][j] == board[i][j+k]){ //Fila
							countH++;
						} else {
							break;
						}
					}
					if(i+k < BOARD_SIZE_X){
						if(board[i][j] == board[i+k][j]){ //Columna
							countV++;
						} else {
							break;
						}
					}
					if(i+k < BOARD_SIZE_X && j+k < BOARD_SIZE_Y){
						if(board[i][j] == board[i+k][j+k]){  // Diagonal1
							countD1++;
						} else {
							break;
						}
					}
					if(i+k < BOARD_SIZE_X && j-k > 0){
						if(board[i][j] == board[i+k][j-k]){  // Diagonal2
							countD2++;
						} else {
							break;
						}
					}
				}
				if(countH >= 5 || countV >= 5 || countD1 >= 5 || countD2 >= 5)
					ret = board[i][j];
			} else {
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

