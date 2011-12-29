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
			distanceEnd = -1;
		}
		void parseString(string str){
			if(str.compare("")!=0){
				char c;
				stringstream ss(stringstream::in | stringstream::out);//create a stringstream
				ss << str;
				ss >> depth;
				ss >> c;
				ss >> h;
				ss >> c;
				ss >> distanceEnd;
			}
		}
		string makeString(){
			string str;
			stringstream ss(stringstream::in | stringstream::out);//create a stringstream
			ss << depth << ";" << h << ";" << distanceEnd;
			ss >> str;
			return str;
		}
};

#endif /* H_NODEEVAL */

