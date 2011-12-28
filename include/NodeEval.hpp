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

		NodeEval(){
			depth = 0;
			h = 0;
			distanceEnd = 0;
		}
		void parseString(string str){
			stringstream ss(stringstream::in | stringstream::out);//create a stringstream
			ss << str;
			ss >> depth;
			ss >> h;
			ss >> distanceEnd;
		}
		string makeString(){
			string str;
			stringstream ss(stringstream::in | stringstream::out);//create a stringstream
			ss << depth << "," << h << "," << distanceEnd;
			ss >> str;
			return str;
		}
};

#endif /* H_NODEEVAL */

