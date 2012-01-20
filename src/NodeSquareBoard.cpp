#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include "NodeSquareBoard.hpp"

using namespace std;

NodeSquareBoard::NodeSquareBoard(int x, int y, int pieceDiff){
	X = x;
	Y = y;
	PieceDiff = pieceDiff;
	board = new int * [X];

	for(int i=0; i<X; i++){
		board[i] = new int [Y];
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

int NodeSquareBoard::changePlayerPiece(int piece){
	if(piece > PieceDiff)
		return piece - PieceDiff;
	else if(piece != 0)
		return piece + PieceDiff;
	else
		return 0;
}
string NodeSquareBoard::generateKey(bool & reversed){
	vector<string> keys;
	stringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8;
	stringstream ss9, ss10, ss11, ss12, ss13, ss14, ss15, ss16;

	int other_turn = nextPlayer(turn);
	if(turn > other_turn)
		reversed = true;
	else
		reversed = false;
	ss1 << turn;//add number to the stream
	ss2 << turn;//add number to the stream
	ss3 << turn;//add number to the stream
	ss4 << turn;//add number to the stream
	ss5 << turn;//add number to the stream
	ss6 << turn;//add number to the stream
	ss7 << turn;//add number to the stream
	ss8 << turn;//add number to the stream
	ss9 << other_turn;//add number to the stream
	ss10 << other_turn;//add number to the stream
	ss11 << other_turn;//add number to the stream
	ss12 << other_turn;//add number to the stream
	ss13 << other_turn;//add number to the stream
	ss14 << other_turn;//add number to the stream
	ss15 << other_turn;//add number to the stream
	ss16 << other_turn;//add number to the stream
	for(int i = 0 ; i < X ; i++){
		for(int j = 0 ; j < Y ; j++){
			ss1 << board[i]			[j];		//Normal
			ss2 << board[X - i - 1]		[j];		//Flip X
			ss3 << board[i]			[Y - j - 1];	//Flip Y
			ss4 << board[X - i - 1]		[Y - j - 1]; 	//Flip XY
			ss5 << board[j]			[i];		//Mirror
			ss6 << board[Y - j - 1]		[i];		//Mirror Flip X
			ss7 << board[j]			[X - i - 1];	//Mirror Flip Y
			ss8 << board[Y - j - 1]		[X - i - 1]; 	//Mirror Flip XY
			ss9 <<  changePlayerPiece(board[i]			[j]);		//Changed plyers Normal
			ss10 << changePlayerPiece(board[X - i - 1]		[j]);		//Changed plyers Flip X
			ss11 << changePlayerPiece(board[i]			[Y - j - 1]);	//Changed plyers Flip Y
			ss12 << changePlayerPiece(board[X - i - 1]		[Y - j - 1]); 	//Changed plyers Flip XY
			ss13 << changePlayerPiece(board[j]			[i]);		//Changed plyers Mirror
			ss14 << changePlayerPiece(board[Y - j - 1]		[i]);		//Changed plyers Mirror Flip X
			ss15 << changePlayerPiece(board[j]			[X - i - 1]);	//Changed plyers Mirror Flip Y
			ss16 << changePlayerPiece(board[Y - j - 1]		[X - i - 1]); 	//Changed plyers Mirror Flip XY
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
	keys.push_back(ss9.str());
	keys.push_back(ss10.str());
	keys.push_back(ss11.str());
	keys.push_back(ss12.str());
	keys.push_back(ss13.str());
	keys.push_back(ss14.str());
	keys.push_back(ss15.str());
	keys.push_back(ss16.str());
	// using function as comp
	sort (keys.begin(), keys.end());
//			sort (keys.begin(), keys.end(), myfunction);

	return keys[0];//return a string with the contents of the stream
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
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void NodeSquareBoard::countNumGlobal(int & playerA, int & playerB, int & free){
	playerA = 0;
	playerB = 0;
	free = 0;
	for(int i=0; i<X; i++){
		for(int j=0; j<Y; j++){
			if(board[i][j] == 0)
				free++;
			if(board[i][j] < PieceDiff)
				playerA++;
			if(board[i][j] >= PieceDiff)
				playerB++;
		}
	}
}
int NodeSquareBoard::countNumInARow(int x, int y, int incX, int incY){
	int countColor = 1;
	int i = 1;
	//Cuenta las piezas del mismo color hacia un lado
	while(x + incX*i < X && y + incY*i < Y && x + incX*i >= 0 && y + incY*i >= 0){
		if (board[x][y] == board[x + incX*i][y + incY*i]){
			countColor++;
		} else {
			break;
		}
		i++;
	}
	i = 1;
	//Cuenta las piezas del mismo color hacia el otro lado
	while(x - incX*i >= 0 && y - incY*i >= 0 && x - incX*i < X && y - incY*i < Y){
		if (board[x][y] == board[x - incX*i][y - incY*i]){
			countColor++;
		} else {
			break;
		}
		i++;
	}
	return countColor;
}

int NodeSquareBoard::countNumFreeInARow(int x, int y, int incX, int incY, int same=0){
	int countFree = 0;
	int i = 1;
	//Se salta las piezas del mismo color en una dirección
	while(x + incX*i < X && y + incY*i < Y && x + incX*i >=0 && y + incY*i >=0){
		if (board[x][y] != board[x + incX*i][y + incY*i]){
			break;
		}
		i++;
	}
	//Cuenta los espacios libres en la misma dirección
	while(x + incX*i < X && y + incY*i < Y && x + incX*i >= 0 && y + incY*i >= 0){
		if (board[x + incX*i][y + incY*i] == 0 || board[x + incX*i][y + incY*i] == same){
			countFree++;
		} else {
			break;
		}
		i++;
	}
	return countFree;
}

