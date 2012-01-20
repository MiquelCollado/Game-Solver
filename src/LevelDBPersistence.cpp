#include <iostream>
#include <string>
#include "LevelDBPersistence.hpp"

using namespace std;

LevelDBPersistence::LevelDBPersistence(){
	db = NULL;
}
LevelDBPersistence::~LevelDBPersistence(){
	close();
	db = NULL;
}

void LevelDBPersistence::open(string name){
	if(db == NULL){
		leveldb::Options options;
		options.create_if_missing = true;
		leveldb::Status status = leveldb::DB::Open(options, name, &db);
		assert(status.ok());
	}
}

string LevelDBPersistence::get(string key){
	string data;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &data);
	if(data.compare("")!=0)
	        cout << "LOAD key: " << key << " str: " << data << endl;

	return data;
}

int LevelDBPersistence::set(string key, string data){
	string value;
	cout << "SAVE key: " << key << " str: " << data << endl;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
	if (s.ok())
		s = db->Delete(leveldb::WriteOptions(), key);
//	if (s.ok())
	s = db->Put(leveldb::WriteOptions(), key, data);
	return s.ok();
}

void LevelDBPersistence::close(){
	if(db != NULL){
		delete db;
		db = NULL;
	}
}

