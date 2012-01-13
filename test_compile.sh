g++ -Wall -O2 -c src/LevelDBPersistence.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -O2 -c src/NodeSquareBoard.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -O2 -c src/TicTacToe.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -O2 -c src/FiveInARow.cpp -Iinclude/ -Ivendors/leveldb/include
g++ -Wall -O2 -Iinclude -Ivendors/leveldb/include/ -o TicTacToe trainers/TicTacToe.cpp LevelDBPersistence.o NodeSquareBoard.o TicTacToe.o vendors/leveldb/libleveldb.a -lpthread
g++ -Wall -O2 -Iinclude -Ivendors/leveldb/include/ -o FiveInARow trainers/FiveInARow.cpp LevelDBPersistence.o NodeSquareBoard.o FiveInARow.o vendors/leveldb/libleveldb.a -lpthread
