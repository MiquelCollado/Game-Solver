#include <iostream>
#include <string>
#include "NodeSquareBoard.hpp"

using namespace std;

NodeSquareBoard::NodeSquareBoard(int x, int y){
	X = x;
	Y = y;
	board = new int * [X];
	for(int i=0; i<X; i++){
		board[i] = new int [Y];
	}
}
NodeSquareBoard::~NodeSquareBoard(){
	for(int i=0; i<X; i++){
		delete(board[i]);
	}
	delete(board);
}

int NodeSquareBoard::countNumInARow(int x, int y, int incX, int incY){
	int countColor = 1;
	int i = 1;
	//Cuenta las piezas del mismo color hacia un lado
	while(x + incX*i < X && y + incY*i < Y){
		if (board[x][y] == board[x + incX*i][y + incY*i]){
			countColor++;
		} else {
			break;
		}
		i++;
	}
	i = 1;
	//Cuenta las piezas del mismo color hacia el otro lado
	while(x - incX*i < X && y - incY*i < Y){
		if (board[x][y] == board[x - incX*i][y - incY*i]){
			countColor++;
		} else {
			break;
		}
		i++;
	}
	return countColor;
}

int NodeSquareBoard::countNumFreeInARow(int x, int y, int incX, int incY){
	int countFree = 0;
	int i = 1;
	//Se salta las piezas del mismo color en una dirección
	while(x + incX*i < X && y + incY*i < Y){
		if (board[x][y] != board[x + incX*i][y + incY*i]){
			break;
		}
		i++;
	}
	//Cuenta los espacios libres en la misma dirección
	while(x + incX*i < X && y + incY*i < Y){
		if (board[x + incX*i][y + incY*i] == BOARD_FREE){
			countFree++;
		} else {
			break;
		}
		i++;
	}
	return countFree;
}

