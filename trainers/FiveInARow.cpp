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
	cfg.Algorithm = ALGORITHM_ALPHABETA;
	cfg.PersistenceUse = true;
	cfg.PersistenceMinDepthToSave = 3;
	cfg.PersistenceName = "DB_FiveInARow";
	cfg.TimeoutUse = false;
	cfg.TimeoutSeconds = 0;
	cfg.SortMoves = true;

	GameSolver<FiveInARow_Node, FiveInARow_Move, LevelDBPersistence> gs(cfg);
	FiveInARow_Node board;
	unsigned char v[] = {
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
		FiveInARow_Move mv = gs.findBestMove(board, 5);
		board.doMove(mv);
		board.print();
	}
	cout << "End" << endl;
}
