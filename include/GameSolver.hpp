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
#include "Move.hpp"
#include "Config.hpp"
#include "Persistence.hpp"

#define GAME_PLAYING 0
#define GAME_WIN_FIRST 1
#define GAME_WIN_SECOND 2
#define GAME_DRAW 3

using namespace std;

template <class Node, class Move, class Persistence>
class GameSolver {
		Config config;
		Persistence persistence;

/*
function integer minimax(node, depth)
    if node is a terminal node or depth <= 0:
        return the heuristic value of node
    α = -∞
    for child in node:                       # evaluation is identical for both players 
        α = max(α, -minimax(child, depth-1))
    return α


*/
		NodeEval minmax(Node & node, int depth){
			NodeEval node_eval;
			bool toSave = false;
			
			if(config.PersistenceUse){
				node_eval.parseString(persistence.get(node.generateKey()));
				if(node_eval.depth >= depth){
					node.print(depth, node_eval);
					return node_eval;
				}
			}
			
			node_eval.depth = depth;
			node_eval.distanceEnd = -1;
			node_eval.h = LONG_MIN;

			if(node.isEndGame()){ //Finish or no moves
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = 0;
node.print(depth, node_eval);
				toSave = true;
			} else if(depth == 0){
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = -1;
node.print(depth, node_eval);
				toSave = true;
			} else {
				vector<Move> moves = node.findMoves();
				for(unsigned int i = 0 ; i < moves.size() ; i++){
					Node node2 = node.dup();
					node2.doMove(moves[i]);
					NodeEval node_eval_tmp = minmax(node2, depth-1);
					node_eval_tmp.h = -node_eval_tmp.h;

//					alpha = max(alpha, moves[i].h);
					if(node_eval.h <= node_eval_tmp.h){
						node_eval.h = node_eval_tmp.h;
//						node_eval.depth = node_eval_tmp.depth + 1;
						node_eval.distanceEnd = node_eval_tmp.distanceEnd;
						if(node_eval.distanceEnd != -1)
							node_eval.distanceEnd++;
						toSave = true;
					}
				}
			}
node.print(depth, node_eval);
			if(config.PersistenceUse && toSave){
				if(depth >= config.PersistenceMinDepthToSave){
					persistence.set(node.generateKey(), node_eval.makeString());
				}
			}

			return node_eval;
		}
/*
function negascout(node, depth, α, β)
    if node is a terminal node or depth = 0
        return the heuristic value of node
    b := β                                             (* initial window is (-β, -α) *)
    foreach child of node
        score := -negascout (child, depth - 1, -b, -α)
        if α < score < β and child is not first child      (* check if null-window failed high *)
            score := -negascout(child, depth - 1, -β, -α)  (* full re-search *)
        α := max(α, score)
        if α ≥ β
            return α                                   (* Beta cut-off *)
        b := α + 1                                     (* set new null window *)
    return α
*/
		NodeEval negascout(Node & node, int depth, int alpha, int beta){
			NodeEval node_eval;
			bool toSave = false;
			
			if(config.PersistenceUse){
				node_eval.parseString(persistence.get(node.generateKey()));
				if(node_eval.depth >= depth){
					node.print(depth, node_eval);
					return node_eval;
				}
			}
			
			node_eval.depth = depth;
			node_eval.distanceEnd = -1;
			node_eval.h = alpha;

			if(node.isEndGame()){ //Finish or no moves
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = 0;
node.print(depth, node_eval);
				toSave = true;
			} else if(depth == 0){
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = -1;
node.print(depth, node_eval);
				toSave = true;
			} else {
				vector<Move> moves = node.findMoves();
				int b = beta;
				for(unsigned int i = 0 ; i < moves.size() ; i++){
					Node node2 = node.dup();
					node2.doMove(moves[i]);
					NodeEval node_eval_tmp = negascout(node2, depth-1, -b, -alpha);
					node_eval_tmp.h = -node_eval_tmp.h;

					if(alpha < node_eval_tmp.h && node_eval_tmp.h < beta && i!=0){
						node_eval_tmp = negascout(node2, depth-1, -beta, -alpha);
						node_eval_tmp.h = -node_eval_tmp.h;
					}
//					alpha = max(alpha, moves[i].h);
					if(alpha <= node_eval_tmp.h){
						alpha = node_eval_tmp.h;
						node_eval.h = node_eval_tmp.h;
//						node_eval.depth = node_eval_tmp.depth + 1;
						node_eval.distanceEnd = node_eval_tmp.distanceEnd;
						if(node_eval.distanceEnd != -1)
							node_eval.distanceEnd++;
						toSave = true;
					}
					if (alpha >= beta) // Beta cut-off
						break;
						//return node_eval;
					b = alpha + 1;
				}
			}
node.print(depth, node_eval);
/* Negascout no puede guardar nodos porque la poda invalida los resultados de los nodos intermedios
			if(config.PersistenceUse && toSave){
				if(depth >= config.PersistenceMinDepthToSave){
					persistence.set(node.generateKey(), node_eval.makeString());
				}
			}
*/
			return node_eval;
		}
	public:
		GameSolver(Config cfg){
			config = cfg;
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
			int best_h;
			int best_distance;
			int num = -1;
			int alpha = LONG_MIN;
			int beta = LONG_MAX;
			vector<Move> moves = node.findMoves();
			NodeEval node_eval;

			for(unsigned int i = 0 ; i < moves.size() ; i++){
				Node node2 = node.dup();
				node2.doMove(moves[i]);
				NodeEval node_eval_tmp;
				if(config.Algorithm == ALGORITHM_NEGASCOUT)
					node_eval_tmp = negascout(node2, depth, alpha, beta);
				else if(config.Algorithm == ALGORITHM_MINMAX)
					node_eval_tmp = minmax(node2, depth);
//				node_eval_tmp.h = -node_eval_tmp.h;
node2.print(depth, node_eval_tmp);
//cout << "Move: " << moves[i].x << ", "  << moves[i].y << ", "  << moves[i].h << ", " << moves[i].player << endl;
				if(i==0){
					node_eval = node_eval_tmp;
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h > best_h){
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
			}
			if(config.PersistenceUse){
				NodeEval node_eval_get;
				node_eval_get.parseString(persistence.get(node.generateKey()));
				if(node_eval_get.depth < depth+1){
					node_eval.h = best_h;
					node_eval.depth = depth + 1;
					node_eval.distanceEnd = best_distance;
					if(node_eval.distanceEnd > -1)
						node_eval.distanceEnd++;
					persistence.set(node.generateKey(), node_eval.makeString());
				}
			}
			cout << "num: " <<  num << endl;
			cout << "node.turn: " <<  node.turn << endl;
			cout << "best_h: " <<  best_h << endl;
			cout << "best_distance: " <<  best_distance << endl;
			return moves[num];

		}
};

#endif /* H_GAMESOLVER */


