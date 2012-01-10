#include "Config.hpp"
#include "TicTacToe.hpp"
//#include "Move.hpp"
#include "GameSolver.hpp"
//#include "NodeEval.hpp"
//#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

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
	int v[] = {1,1,0,0,2,0,0,0,0};
	board.init(v);
	board.turn = 1;
	TicTacToe_Move mv = gs.findBestMove(board, 10);
	board.doMove(mv);
	board.print();

}
