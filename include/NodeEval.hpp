#ifndef H_NODEEVAL
#define H_NODEEVAL

#include <sstream>
#include <string>

using namespace std;

class NodeEval {
	public:
		int depth;
		int h;
		int distanceEnd;
		string str;

		NodeEval(){
			depth = 0;
			h = 0;
			distanceEnd = 0;
			str = "";
		}
		void parseStr(){
			stringstream ss(stringstream::in | stringstream::out);//create a stringstream
			ss << str;
			ss >> depth;
			ss >> h;
			ss >> distanceEnd;
		}
		void makeStr(){
			stringstream ss(stringstream::in | stringstream::out);//create a stringstream
			ss << depth << "," << h << "," << distanceEnd;
			ss >> str;
		}
};

#endif /* H_NODEEVAL */

