#ifndef H_LEVELDBPERSISTENCE
#define H_LEVELDBPERSISTENCE

#include <string>
#include "Persistence.hpp"
#include "leveldb/db.h"

using namespace std;

class LevelDBPersistence: public Persistence {
		leveldb::DB* db;
	public:
		LevelDBPersistence();
		int open(string name);
		string get(string key);
		int set(string key, string data);
		int close();
};

#endif /* H_LEVELDBPERSISTENCE */


