g++ -Wall -Iinclude -Ivendors/leveldb/include/ -o pp src/TicTacToe.cpp src/LevelDBPersistence.cpp vendors/leveldb/libleveldb.a -lpthread

