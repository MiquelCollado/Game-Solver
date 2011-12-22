#ifndef H_CONFIG
#define H_CONFIG

#include <string>

using namespace std;

class Config {
	public:
		bool	DbUse;
		int	DbMinDepthToSave;
		string	DbFilename;
		bool	TimeoutUse;
		int	TimeoutSeconds;
};

#endif /* H_CONFIG */

