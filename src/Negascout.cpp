#include "Config.hpp"
#include "Node.hpp"
#include "Move.hpp"
#include "Negascout.hpp"
#include "NodeEval.hpp"

int main(){
	Config cfg;
	Move move;
	NodeEval nodeeval;
	Node node;
	Cache cache;
	Negascout ns(node, move, cfg, cache);
}

