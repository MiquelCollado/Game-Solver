#ifndef H_GAMESOLVER
#define H_GAMESOLVER

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
//#include "Move.hpp"
#include "Config.hpp"
#include "Persistence.hpp"

#define GAME_PLAYING 0
#define GAME_WIN_FIRST 1
#define GAME_WIN_SECOND 2
#define GAME_DRAW 3

#define MAX 1
#define MIN 2

using namespace std;

template <class Node, class Move, class Persistence>
class GameSolver {
		Config config;
		Persistence persistence;
		bool pruned;

/*
function alphabeta(node, depth, α, β, Player)
	if  depth = 0 or node is a terminal node
		return the heuristic value of node
	if  Player = MaxPlayer
		for each child of node
			α := max(α, alphabeta(child, depth-1, α, β, not(Player) ))
			if β ≤ α
				break                             (* Beta cut-off *)
		return α
	else
		for each child of node
			β := min(β, alphabeta(child, depth-1, α, β, not(Player) ))
			if β ≤ α
				break                             (* Alpha cut-off *)
		return β
(* Initial call *)
alphabeta(origin, depth, -infinity, +infinity, MaxPlayer)
*/
		static bool sortMax (Move i,Move j) {
			bool ret;
			if(i.data.h > j.data.h){
				ret = true;
			} else if(i.data.h == j.data.h && i.data.distanceEnd < j.data.distanceEnd && i.data.distanceEnd != -1){
				ret = true;
			} else {
				ret = false;
			}
			return ret;
		}
		static bool sortMin (Move i,Move j) {
			bool ret;
			if(i.data.h < j.data.h){
				ret = true;
			} else if(i.data.h == j.data.h && i.data.distanceEnd > j.data.distanceEnd && j.data.distanceEnd != -1){
				ret = true;
			} else {
				ret = false;
			}
			return ret;
		}

		void sortMoves(Node & node, vector<Move> & moves, int order){
			typename vector<Move>::iterator it;
			typename vector<Move>::iterator it2, it_old;
			bool reversed = false;
			string key;

			if(moves.size() > 0){
				for(unsigned int i = 0 ; i < moves.size() ; i++){
					Node node2 = node.dup();
					node2.doMove(moves[i]);
					moves[i].key = node2.generateKey(reversed);
					if(config.PersistenceUse){
						moves[i].data.parseString(persistence.get(moves[i].key));
						if(moves[i].data.depth != 0){
							if(reversed)
								moves[i].data.h = -moves[i].data.h;
						} else {
							moves[i].data.depth = 0;
							moves[i].data.distanceEnd = -1;
							moves[i].data.h = node2.heuristic();;
						}
					} else {
						moves[i].data.h = node2.heuristic();;
					}
				}
				if(order == MAX)
					sort(moves.begin(), moves.end(), GameSolver::sortMax);
				else
					sort(moves.begin(), moves.end(), GameSolver::sortMin);

				it = moves.begin();
				it_old= it;
				if(it != moves.end())
					++it;
				while(it != moves.end()){
					if((*it_old).key.compare((*it).key) == 0)
						it = moves.erase(it);
					else{
						it_old = it;
						++it;
					}
				}
			}
		}

		NodeEval alphabeta(Node & node, int depth, int alpha, int beta){
			NodeEval node_eval;
			bool toSave = false;
			bool reversed = false;
			string key;

			if(config.PersistenceUse && depth > 0){
				key = node.generateKey(reversed);
				node_eval.parseString(persistence.get(key));
				if(node_eval.depth >= depth && node_eval.depth != 0){
					if(reversed)
						node_eval.h = -node_eval.h;
//					node.print(depth, node_eval);
					return node_eval;
				}
			}

			node_eval.depth = depth;
			node_eval.distanceEnd = -1;

			if(node.isEndGame()){ //Finish or no moves
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = 0;
//node.print(depth, node_eval);
				toSave = true;
			} else if(depth == 0){
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = -1;
//node.print(depth, node_eval);
				toSave = true;
			} else {
				vector<Move> moves = node.findMoves();
				if(config.SortMoves){
					sortMoves(node, moves, node.turn);
				}
				if(node.turn == 1){ // MAX
					node_eval.h = alpha;
					for(unsigned int i = 0 ; i < moves.size() ; i++){
						Node node2 = node.dup();
						node2.doMove(moves[i]);
						NodeEval node_eval_tmp = alphabeta(node2, depth-1, alpha, beta);

						// α := max(α, alphabeta(child, depth-1, α, β, not(Player) ))
						if(alpha <= node_eval_tmp.h){
							alpha = node_eval_tmp.h;
							node_eval.h = node_eval_tmp.h;
//							node_eval.depth = node_eval_tmp.depth + 1;
							node_eval.distanceEnd = node_eval_tmp.distanceEnd;
							if(node_eval.distanceEnd != -1)
								node_eval.distanceEnd++;
							toSave = true;
						}
						if (alpha >= beta && config.Algorithm == ALGORITHM_ALPHABETA){ // Beta cut-off
							pruned = true;
							break;
						}
						//return node_eval;
					}
				} else { // MIN /**/
					node_eval.h = beta;
					for(unsigned int i = 0 ; i < moves.size() ; i++){
						Node node2 = node.dup();
						node2.doMove(moves[i]);
						NodeEval node_eval_tmp = alphabeta(node2, depth-1, alpha, beta);

						// β := min(β, alphabeta(child, depth-1, α, β, not(Player) ))
						if(beta >= node_eval_tmp.h){
							beta = node_eval_tmp.h;
							node_eval.h = node_eval_tmp.h;
//							node_eval.depth = node_eval_tmp.depth + 1;
							node_eval.distanceEnd = node_eval_tmp.distanceEnd;
							if(node_eval.distanceEnd != -1)
								node_eval.distanceEnd++;
							toSave = true;
						}
						if (alpha >= beta && config.Algorithm == ALGORITHM_ALPHABETA){ // Beta cut-off
							pruned = true;
							break;
						}
						//return node_eval;
					}
				}
			}
//node.print(depth, node_eval);
			if(config.PersistenceUse && toSave && !pruned){
				if(depth >= config.PersistenceMinDepthToSave){
//					bool reversed = false;
//					string key = node.generateKey(reversed);
					if(reversed)
						node_eval.h = -node_eval.h;
					persistence.set(key, node_eval.makeString());
					if(reversed)
						node_eval.h = -node_eval.h;
				}
			}
			return node_eval;
		}
	public:
		GameSolver(Config cfg){
			config = cfg;
			pruned = false;
			if(config.PersistenceUse){
				persistence.open(config.PersistenceName);
			}
		}
		~GameSolver(){
			if(config.PersistenceUse){
				persistence.close();
			}
		}
		Move findBestMove(Node & node, int depth){
			int best_h = 0;
			int best_distance = -1;
			int num = -1;
			NodeEval node_eval;

			vector<Move> moves = node.findMoves();
			if(config.SortMoves){
				sortMoves(node, moves, node.turn);
			}
/*			for(unsigned int i = 0 ; i < moves.size() ; i++){
				cout << "Move: " << moves[i].x << ", "  << moves[i].y << ", " << moves[i].data.h << ", " << moves[i].data.distanceEnd << ", " << moves[i].data.depth << endl;
			}
			exit(0);*/
			for(unsigned int i = 0 ; i < moves.size() ; i++){
				Node node2 = node.dup();
				node2.doMove(moves[i]);
				NodeEval node_eval_tmp;
//cout << "Move1: " << moves[i].x << ", "  << moves[i].y << ", " << moves[i].player << endl;
				if(config.Algorithm == ALGORITHM_ALPHABETA){
					pruned = false;
					node_eval_tmp = alphabeta(node2, depth, LONG_MIN, LONG_MAX);
				}else if(config.Algorithm == ALGORITHM_MINMAX){
					pruned = false;
					node_eval_tmp = alphabeta(node2, depth, LONG_MIN, LONG_MAX);
				}
//node2.print(depth, node_eval_tmp);
//cout << "Move2: " << moves[i].x << ", "  << moves[i].y << ", " << moves[i].player << endl;
				if(i==0){
					node_eval = node_eval_tmp;
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h > best_h && node.turn == 1){ // MAX
					node_eval = node_eval_tmp;
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h < best_h && node.turn != 1){ // MIN
					node_eval = node_eval_tmp;
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h == best_h && node_eval_tmp.distanceEnd < best_distance){
					node_eval = node_eval_tmp;
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				}

				if(config.PersistenceUse && depth >= config.PersistenceMinDepthToSave){
					bool reversed = false;
					NodeEval node_eval_get;
					string key = node2.generateKey(reversed);
					node_eval_get.parseString(persistence.get(key));
					if(node_eval_get.depth < depth){
						if(reversed)
							node_eval_tmp.h = -node_eval_tmp.h;
						node_eval_tmp.depth = depth;
						persistence.set(key, node_eval_tmp.makeString());
						if(reversed)
							node_eval_tmp.h = -node_eval_tmp.h;
					}
				}

				/*
				bool reversed = false;
				string key = node.generateKey(reversed);
				if(reversed)
				node_eval.h = -node_eval.h;
				persistence.set(key, node_eval.makeString());
				node_eval.h = -node_eval.h;
			}
				*/
			}
			if(config.PersistenceUse && depth+1 >= config.PersistenceMinDepthToSave){
				bool reversed = false;
				NodeEval node_eval_get;
				string key = node.generateKey(reversed);
				node_eval_get.parseString(persistence.get(key));
				if(node_eval_get.depth < depth+1){
					node_eval.h = best_h;
					node_eval.depth = depth + 1;
					node_eval.distanceEnd = best_distance;
					if(node_eval.distanceEnd > -1)
						node_eval.distanceEnd++;
//					string key = node.generateKey(reversed);
					if(reversed)
						node_eval.h = -node_eval.h;
					persistence.set(key, node_eval.makeString());
					if(reversed)
						node_eval.h = -node_eval.h;
				}
			}
//			cout << "num: " <<  num << endl;
//			cout << "node.turn: " <<  node.turn << endl;
//			cout << "best_h: " <<  best_h << endl;
//			cout << "best_distance: " <<  best_distance << endl;
			return moves[num];

		}
};

#endif /* H_GAMESOLVER */


