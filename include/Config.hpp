#ifndef H_CONFIG
#define H_CONFIG

#define ALGORITHM_MINMAX	1
#define ALGORITHM_ALPHABETA	2

#include <string>

using namespace std;

class Config {
	public:
		int		Algorithm;
		bool	PersistenceUse;
		int		PersistenceMinDepthToSave;
		string	PersistenceName;
		bool	TimeoutUse;
		int		TimeoutSeconds;
		bool	SortMoves;

		Config(){
			Algorithm = ALGORITHM_ALPHABETA;
			PersistenceUse = false;
			PersistenceMinDepthToSave = 0;
			PersistenceName = "";
			TimeoutUse = false;
			TimeoutSeconds = 0;
			SortMoves = false;
		}
};

#endif /* H_CONFIG */

