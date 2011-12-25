#ifndef H_NEGASCOUT
#define H_NEGASCOUT

#include <stddef.h>
#include <assert.h>
#include <limits.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#include "Node.hpp"
#include "NodeEval.hpp"
#include "Move.hpp"
#include "Config.hpp"
#include "Cache.hpp"

using namespace std;

class Negascout {
	public:
		Negascout(Node, Move, Config, Cache);
		~Negascout();
		Move findBestMove(Node & _node, int depth);
		NodeEval negascout(Node & node, int depth, int & alpha, int & beta);

};

#endif /* H_NEGASCOUT */


