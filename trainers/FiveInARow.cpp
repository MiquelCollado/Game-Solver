#include "Config.hpp"
#include "FiveInARow.hpp"
//#include "Move.hpp"
#include "GameSolver.hpp"
//#include "NodeEval.hpp"
//#include "Persistence.hpp"

#include "LevelDBPersistence.hpp"

int main(){
	Config cfg;
//	cfg.Algorithm = ALGORITHM_MINMAX;
	cfg.Algorithm = ALGORITHM_NEGASCOUT;
	cfg.PersistenceUse = true;
	cfg.PersistenceMinDepthToSave = 2;
	cfg.PersistenceName = "DB_FiveInARow";
	cfg.TimeoutUse = false;
	cfg.TimeoutSeconds = 0;

	GameSolver<FiveInARow_Node, FiveInARow_Move, LevelDBPersistence> gs(cfg);
	FiveInARow_Node board;
	int v[] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0
	};
	board.init(v);
	board.turn = 1;
	while(!board.isEndGame()){
		FiveInARow_Move mv = gs.findBestMove(board, 4);
		board.doMove(mv);
		board.print();
	}
}
