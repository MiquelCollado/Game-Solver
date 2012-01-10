g++ -c src/LevelDBPersistence.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -c src/NodeSquareBoard.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -c src/TicTacToe.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -Iinclude -Ivendors/leveldb/include/ -o pp trainers/TicTacToe.cpp LevelDBPersistence.o NodeSquareBoard.o TicTacToe.o vendors/leveldb/libleveldb.a -lpthread

