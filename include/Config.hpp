#ifndef H_CONFIG
#define H_CONFIG

#include <string>

using namespace std;

class Config {
	public:
		bool	PersistenceUse;
		int	PersistenceMinDepthToSave;
		string	PersistenceName;
		bool	TimeoutUse;
		int	TimeoutSeconds;

		Config(){
			PersistenceUse = false;
			PersistenceMinDepthToSave = 0;
			PersistenceName = "";
			TimeoutUse = false;
			TimeoutSeconds = 0;
		}
};

#endif /* H_CONFIG */

