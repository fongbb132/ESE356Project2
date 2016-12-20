#include <map>
#include <unordered_set>
struct pair {
  int robot;
  int step; 
} ;

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