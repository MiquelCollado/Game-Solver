#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "NodeSquareBoard.hpp"

using namespace std;

NodeSquareBoard::NodeSquareBoard(int x, int y, unsigned char pieceDiff){
	X = x;
	Y = y;
	PieceDiff = pieceDiff;
	board = new unsigned char * [X];

	for(int i=0; i<X; i++){
		board[i] = new unsigned char [Y];
		for(int j = 0 ; j < Y ; j++){
			board[i][j] = 0;
		}
	}
}
NodeSquareBoard::~NodeSquareBoard(){
	for(int i=0; i<X; i++){
		delete(board[i]);
	}
	delete(board);
}

string NodeSquareBoard::generateKey(bool & reversed){
	unsigned char ckeys[8][X*Y+1+1];
	int i, j, k;

	int other_turn = nextPlayer(turn);
	if(turn > other_turn)
		reversed = true;
	else
		reversed = false;
	unsigned char *ckey0 = ckeys[0];
	unsigned char *ckey1 = ckeys[1];
	unsigned char *ckey2 = ckeys[2];
	unsigned char *ckey3 = ckeys[3];
	unsigned char *ckey4 = ckeys[4];
	unsigned char *ckey5 = ckeys[5];
	unsigned char *ckey6 = ckeys[6];
	unsigned char *ckey7 = ckeys[7];
	if(turn == 1){
		unsigned char t = '0' + (unsigned char)turn;
		*(ckey0++) = t;
		*(ckey1++) = t;
		*(ckey2++) = t;
		*(ckey3++) = t;
		*(ckey4++) = t;
		*(ckey5++) = t;
		*(ckey6++) = t;
		*(ckey7++) = t;
//		for(i=0;i<8;i++)
//			ckeys[i][0] = '0' + (unsigned char)turn;
	} else {
		unsigned char t = '0' + (unsigned char)other_turn;
		*(ckey0++) = t;
		*(ckey1++) = t;
		*(ckey2++) = t;
		*(ckey3++) = t;
		*(ckey4++) = t;
		*(ckey5++) = t;
		*(ckey6++) = t;
		*(ckey7++) = t;
//		for(i=0;i<8;i++)
//			ckeys[i][0] = '0' + (unsigned char)other_turn;
	}

	k = 1;
	if(turn == 1){
		for(i = 0 ; i < X ; i++){
			for(j = 0 ; j < Y ; j++){
				*(ckey0++) = '0' + board[i]			[j];		//Normal
				*(ckey1++) = '0' + board[X - i - 1]		[j];		//Flip X
				*(ckey2++) = '0' + board[i]			[Y - j - 1];	//Flip Y
				*(ckey3++) = '0' + board[X - i - 1]		[Y - j - 1]; 	//Flip XY
				*(ckey4++) = '0' + board[j]			[i];		//Mirror
				*(ckey5++) = '0' + board[Y - j - 1]		[i];		//Mirror Flip X
				*(ckey6++) = '0' + board[j]			[X - i - 1];	//Mirror Flip Y
				*(ckey7++) = '0' + board[Y - j - 1]		[X - i - 1]; 	//Mirror Flip XY
/*				ckeys[0][k] = '0' + board[i]			[j];		//Normal
				ckeys[1][k] = '0' + board[X - i - 1]		[j];		//Flip X
				ckeys[2][k] = '0' + board[i]			[Y - j - 1];	//Flip Y
				ckeys[3][k] = '0' + board[X - i - 1]		[Y - j - 1]; 	//Flip XY
				ckeys[4][k] = '0' + board[j]			[i];		//Mirror
				ckeys[5][k] = '0' + board[Y - j - 1]		[i];		//Mirror Flip X
				ckeys[6][k] = '0' + board[j]			[X - i - 1];	//Mirror Flip Y
				ckeys[7][k] = '0' + board[Y - j - 1]		[X - i - 1]; 	//Mirror Flip XY*/
				k++;
			}
		}
	} else {
		for(i = 0 ; i < X ; i++){
			for(j = 0 ; j < Y ; j++){
				*(ckey0++) = '0' + changePlayerPiece(board[i]			[j]);		//Changed players Normal
				*(ckey1++) = '0' + changePlayerPiece(board[X - i - 1]		[j]);		//Changed players Flip X
				*(ckey2++) = '0' + changePlayerPiece(board[i]			[Y - j - 1]);	//Changed players Flip Y
				*(ckey3++) = '0' + changePlayerPiece(board[X - i - 1]		[Y - j - 1]); 	//Changed players Flip XY
				*(ckey4++) = '0' + changePlayerPiece(board[j]			[i]);		//Changed players Mirror
				*(ckey5++) = '0' + changePlayerPiece(board[Y - j - 1]		[i]);		//Changed players Mirror Flip X
				*(ckey6++) = '0' + changePlayerPiece(board[j]			[X - i - 1]);	//Changed players Mirror Flip Y
				*(ckey7++) = '0' + changePlayerPiece(board[Y - j - 1]		[X - i - 1]); 	//Changed players Mirror Flip XY
/*				ckeys[0][k] = '0' + changePlayerPiece(board[i]			[j]);		//Changed players Normal
				ckeys[1][k] = '0' + changePlayerPiece(board[X - i - 1]		[j]);		//Changed players Flip X
				ckeys[2][k] = '0' + changePlayerPiece(board[i]			[Y - j - 1]);	//Changed players Flip Y
				ckeys[3][k] = '0' + changePlayerPiece(board[X - i - 1]		[Y - j - 1]); 	//Changed players Flip XY
				ckeys[4][k] = '0' + changePlayerPiece(board[j]			[i]);		//Changed players Mirror
				ckeys[5][k] = '0' + changePlayerPiece(board[Y - j - 1]		[i]);		//Changed players Mirror Flip X
				ckeys[6][k] = '0' + changePlayerPiece(board[j]			[X - i - 1]);	//Changed players Mirror Flip Y
				ckeys[7][k] = '0' + changePlayerPiece(board[Y - j - 1]		[X - i - 1]); 	//Changed players Mirror Flip XY*/
				k++;
			}
		}
	}
	*(ckey0++) = 0;
	*(ckey1++) = 0;
	*(ckey2++) = 0;
	*(ckey3++) = 0;
	*(ckey4++) = 0;
	*(ckey5++) = 0;
	*(ckey6++) = 0;
	*(ckey7++) = 0;
//	for(i=0;i<8;i++) // Ending strings
//		ckeys[i][k] = 0;

	k=0;
	for(i=1;i<8;i++){ // Sort
		if(strcmp((const char *)ckeys[k], (const char *)ckeys[i]) > 0)
			k = i;
	}
	string ret((const char *)ckeys[k]);
//	cout << ret << endl;
//	exit(0);
	return ret;
}
void NodeSquareBoard::print(int depth, NodeEval data){
	string pre(12 - depth,  ' ');
	cout << pre << "heuristic: " << data.h << endl;
	cout << pre << "distanceEnd: " << data.distanceEnd << endl;
	cout << pre << "depth: " << data.depth << endl;
	print();
}
void NodeSquareBoard::print(){
	cout << "turn: " << turn << endl;
	for(int j = 0 ; j < Y ; j++){
		for(int i = 0 ; i < X ; i++){
			cout << (int) board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void NodeSquareBoard::countNumGlobal(int & playerA, int & playerB, int & free){
	playerA = 0;
	playerB = 0;
	free = 0;
//	unsigned char *p = &board[0][0];
	for(int i=0; i<X; i++){
		for(int j=0; j<Y; j++){
			unsigned char p = board[i][j];
			if(p == 0)
				free++;
			if(p < PieceDiff)
				playerA++;
			if(p >= PieceDiff)
				playerB++;
		}
	}
}
int NodeSquareBoard::countNumInARow(int x, int y, int incX, int incY){
	int countColor = 1;
	int i = 1;
	//Cuenta las piezas del mismo color hacia un lado
	unsigned char p = board[x][y];
	int _x1 = x + incX*i;
	int _y1 = y + incY*i;
	while(_x1 < X && _y1 < Y && _x1 >= 0 && _y1 >= 0){
		if (p == board[_x1][_y1]){
			countColor++;
		} else {
			break;
		}
		i++;
		_x1 = x + incX*i;
		_y1 = y + incY*i;
	}
	i = 1;
	_x1 = x - incX*i;
	_y1 = y - incY*i;
	//Cuenta las piezas del mismo color hacia el otro lado
	while(_x1 >= 0 && _y1 >= 0 && _x1 < X && _y1 < Y){
		if (p == board[_x1][_y1]){
			countColor++;
		} else {
			break;
		}
		i++;
		_x1 = x - incX*i;
		_y1 = y - incY*i;
	}
	return countColor;
}

int NodeSquareBoard::countNumFreeInARow(int x, int y, int incX, int incY, unsigned char same=0){
	int countFree = 0;
	int i = 1;
	//Se salta las piezas del mismo color en una dirección
	int _x1 = x + incX*i;
	int _y1 = y + incY*i;
	unsigned char p = board[x][y];
	while(_x1 < X && _y1 < Y && _x1 >=0 && _y1 >=0){
		if (p != board[_x1][_y1]){
			break;
		}
		i++;
		_x1 = x + incX*i;
		_y1 = y + incY*i;
	}
	//Cuenta los espacios libres en la misma dirección
	while(_x1 < X && _y1 < Y && _x1 >= 0 && _y1 >= 0){
		if (board[_x1][_y1] == 0 || board[_x1][_y1] == same){
			countFree++;
		} else {
			break;
		}
		i++;
		_x1 = x + incX*i;
		_y1 = y + incY*i;
	}
	return countFree;
}

