#ifndef H_CONFIG
#define H_CONFIG

#define ALGORITHM_MINMAX	1
#define ALGORITHM_NEGASCOUT	2

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

		Config(){
			Algorithm = ALGORITHM_NEGASCOUT;
			PersistenceUse = false;
			PersistenceMinDepthToSave = 0;
			PersistenceName = "";
			TimeoutUse = false;
			TimeoutSeconds = 0;
		}
};

#endif /* H_CONFIG */

