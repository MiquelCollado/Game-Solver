#ifndef H_PERSISTENCE
#define H_PERSISTENCE

#include <string>

using namespace std;

class Persistence {
	public:
		virtual int open(string name)=0;
		virtual string get(string key)=0;
		virtual int set(string key, string data)=0;
		virtual int close()=0;
};

#endif /* H_PERSISTENCE */

