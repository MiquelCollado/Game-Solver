g++ -c src/LevelDBPersistence.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -c src/NodeSquareBoard.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -Iinclude -Ivendors/leveldb/include/ -o pp src/TicTacToe.cpp LevelDBPersistence.o NodeSquareBoard.o vendors/leveldb/libleveldb.a -lpthread


