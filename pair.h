#include <map>
struct pair {
  int robot;
  int step; 
} ;

struct pairList{
	std::vector<pair*> pairList;
};

struct loc{
	int col; 
	int row;
};