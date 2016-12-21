#include <map>
#include <unordered_set>

//record how many steps a robot take to go to a node
struct pair {
  int robot;
  int step; 
} ;

//table to record 
struct pairList{
	std::map< int, pair*> pairList;
};

struct numList{
	std::vector<int> numList;
};

struct loc{
	int col; 
	int row;
};

struct robotsNode
{
	std::unordered_set<int> robotList; 
};