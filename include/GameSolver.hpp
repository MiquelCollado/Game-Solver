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
			node_eval.depth = depth;
			node_eval.distanceEnd = -1;
			node_eval.h = alpha;

			if(node.isEndGame()){ //Finish or no moves
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = 0;
node.print(depth, node_eval);
			} else if(depth == 0){
				node_eval.h = node.heuristic();
				node_eval.distanceEnd = -1;
node.print(depth, node_eval);
			} else {
				vector<Move> moves = node.findMoves();
				int b = beta;
				for(unsigned int i = 0 ; i < moves.size() ; i++){
					Node node2 = node.dup();
					node2.doMove(moves[i]);
					NodeEval node_eval_tmp = negascout(node2, depth-1, -b, -alpha);
					node_eval_tmp.h = -node_eval_tmp.h;
node2.print(depth-1, node_eval_tmp);
					if(alpha < node_eval_tmp.h && node_eval_tmp.h < beta && i!=0){
						node_eval_tmp = negascout(node2, depth-1, -beta, -alpha);
						node_eval_tmp.h = -node_eval_tmp.h;
node2.print(depth-1, node_eval_tmp);
					}
//					alpha = max(alpha, moves[i].h);
					if(alpha <= node_eval_tmp.h){
						alpha = node_eval_tmp.h;
						node_eval.h = node_eval_tmp.h;
						node_eval.depth = node_eval_tmp.depth;
						node_eval.distanceEnd = node_eval_tmp.distanceEnd;
						if(node_eval.distanceEnd != -1)
							node_eval.distanceEnd++;
					}
					if (alpha >= beta) // Beta cut-off
						return node_eval;
					b = alpha + 1;
				}
			}
			return node_eval;
		}
	public:
		GameSolver(Config cfg){
			config = cfg;
		}
		~GameSolver(){
		}
		Move findBestMove(Node & node, int depth){
			int best_h;
			int best_distance;
			int num = -1;
			int alpha = LONG_MIN;
			int beta = LONG_MAX;
			vector<Move> moves = node.findMoves();

			for(unsigned int i = 0 ; i < moves.size() ; i++){
				Node node2 = node.dup();
				node2.doMove(moves[i]);
				NodeEval node_eval_tmp = negascout(node2, depth, alpha, beta);
//				node_eval_tmp.h = -node_eval_tmp.h;
node2.print(depth, node_eval_tmp);
//cout << "Move: " << moves[i].x << ", "  << moves[i].y << ", "  << moves[i].h << ", " << moves[i].player << endl;
				if(i==0){
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h > best_h){
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
				} else if(node_eval_tmp.h == best_h && node_eval_tmp.distanceEnd < best_distance){ 
					best_h = node_eval_tmp.h;
					best_distance = node_eval_tmp.distanceEnd;
					num = i;
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


