#include "Config.hpp"
#include "FiveInARow.hpp"
//#include "Move.hpp"
#include "GameSolver.hpp"
//#include "NodeEval.hpp"
//#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

int main(){
	Config cfg;
	cfg.Algorithm = ALGORITHM_MINMAX;
	cfg.PersistenceUse = true;
	cfg.PersistenceMinDepthToSave = 6;
	cfg.PersistenceName = "DB_FiveInARow";
	cfg.TimeoutUse = false;
	cfg.TimeoutSeconds = 0;

	GameSolver<FiveInARow_Node, FiveInARow_Move, LevelDBPersistence> gs(cfg);
	FiveInARow_Node board;
//	int v[] = {1,1,0,0,2,0,0,0,0};
//	board.init(v);
	board.turn = 1;
	FiveInARow_Move mv = gs.findBestMove(board, 10);
	board.doMove(mv);
	board.print();
}
