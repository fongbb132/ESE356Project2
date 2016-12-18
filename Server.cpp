#include "Server.h"
#include <fstream> 
#include "pair.h"

void Server::nodeOrdering(){
	std::map<int, pairList*> map;

	for(int node: nodes){
		map.insert(std::make_pair(node, new pairList())) ;
	}

	for(int j = 0 ; j < numRobot ; j++){
		for(int i = 0 ; i < numPath; i++ ){
			if(map.find(path[j][i]) != map.end()){
				pairList *temp = map.find(path[j][i])->second; 
				pair *newpair = new pair(); 
				newpair->robot = j; 
				newpair->step = i; 
				temp->pairList.push_back(newpair); 
			}
		}
	}

	for(auto iterator = map.begin(); iterator != map.end(); iterator++) {
	    cout<<iterator->first<<" " ;
	    for(int i = 0 ; i < iterator->second->pairList.size(); i++){
	    	cout<<iterator->second->pairList[i]->robot << " " <<"at step " << iterator->second->pairList[i]->step <<"   ";
	        // Repeat if you also want to iterate through the second map.
	    }
	    cout<<" " <<endl;
	}
}


void Server::loadPath(){
	ifstream myfile; 
	myfile.open("input.txt"); 
	for(int i = 0; i < numGrid; i++){
		myfile>>map[i];
	}

	for(int i = 0; i < numRow ; i++){
		for(int j = 0 ; j < numCol; j++){
			map_2d[i][j]=0; 
		}
	}
	for(int i =0 ; i < 8  ; i++){
		int dumb;
		myfile>>dumb; 
	}
	int numSquare;
	myfile>>numSquare; 
	for(int i = 0 ; i < numSquare ; i++){
		int lowX, lowY, highX, highY; 

		myfile>>lowX>>lowY>>highX>>highY; 
		cout<<lowX<<lowY<<highX<<highY;
		for(int i = lowX ; i<highX; i++){
			for(int j = lowY; j<highY; j++){
				map_2d[j][i] = 1;
			}
		}
	}


	myfile.close(); 

	int rowReduced = 0; 
	int colReduced = 0; 

	for(int i = 1 ; i < numRow; i++){
		bool has1 = false; 

		for(int j = 0 ; j < numCol; j++){
			if(map_2d[i][j] == 1) {
				has1 = true;
				break; 
			}
		}

		if(!has1){
			rowReduced++; 
		}
		for(int j = 0 ; j < numCol; j++){
			map_2d[i-rowReduced][j] = map_2d[i][j] ;
		}
	}

	for(int i = 11 ; i < numRow; i++){
	
		for(int j = 0 ; j < numCol; j++){
			map_2d[i-3][j] = map_2d[i][j] ;
		}
	}

	for(int i = 1 ; i < numCol; i++){
		bool has1 = false; 

		for(int j = 0 ; j < numRow; j++){
			if(map_2d[j][i] == 1) {
				has1 = true;
				break; 
			}
		}

		if(!has1){
			colReduced++; 
		}
		for(int j = 0 ; j < numRow; j++){
			map_2d[j][i-colReduced] = map_2d[j][i] ;
		}
	}

	for(int i = 16 ; i <=54; i++){
		for(int j = 0 ; j < numRow; j++){
			map_2d[j][i-7] = map_2d[j][i] ;
		}
	}

	for(int i = 12 ; i <=54; i++){
		for(int j = 0 ; j < numRow; j++){
			map_2d[j][i-2] = map_2d[j][i] ;
		}
	}

	for(int i = 26 ; i <=54; i++){
		for(int j = 0 ; j < numRow; j++){
			map_2d[j][i-5] = map_2d[j][i] ;
		}
	}

	for(int i = 32 ; i <=54; i++){
		for(int j = 0 ; j < numRow; j++){
			map_2d[j][i-8] = map_2d[j][i] ;
		}
	}

	nRow = numRow - rowReduced -3; 
	nCol = numCol - colReduced - 7- 2-5-8;
	int count = 1; 
	for(int i = 0 ; i < nRow; i++){
		for(int j = 0 ; j < nCol ; j++){
			if(map_2d[i][j] == 0)
				map_2d[i][j] = count++; 
		}
	}

	cout<<numRow << "  " << numCol << " " <<rowReduced<<" " << colReduced << " " 
	<< nRow << " " << nCol <<endl;
	for(int i = 0; i < nRow ; i++){
		for(int j = 0 ; j < nCol; j++){
			printf("%3d|", map_2d[i][j]); 
		}
		cout<<endl;
	}

	myfile.open("path.txt"); 
	int numPaths = 0 ; 
	myfile>> numPaths;
	for(int i = 0 ; i < numPaths ; i++){
		int numP = 0 ; 
		myfile>>numP;

		std::vector<int> paths;
		for(int j = 0 ; j < numP ; j ++){
			int temp = 0 ; 
			myfile >> temp;
			paths.push_back(temp); 
		}

		path.push_back(paths); 
	}
	
	int numNodes = 0 ; 
	myfile>>numNodes;

	for(int i = 0 ; i < numNodes ; i++){
		int temp = 0 ; 
		myfile>>temp; 
		nodes.push_back(temp);
	}
	myfile.close(); 
	nodeOrdering();
}


void Server::sendPath(){
	bool finished1 = false; 
	bool finished2 = false; 
	bool finished3 = false; 
	int pathIndex1 = 0; 
	int pathIndex2 = 0 ; 
	int pathIndex3 = 0; 

	while(true){

		if(pathIndex1 < path[0].size()){
			path_out_env[0].write(path[0][pathIndex1]);
			path_out_robot[0].write(path[0][pathIndex1++]);
		}else{
			finished1 = true; 
		}


		if(pathIndex2 < path[1].size()){
			path_out_env[1].write(path[1][pathIndex2]);
			path_out_robot[1].write(path[1][pathIndex2++]);
		}else{
			finished2 = true; 
		}


		if(pathIndex3 < path[2].size()){
			path_out_env[2].write(path[2][pathIndex3]);
			path_out_robot[2].write(path[2][pathIndex3++]);
		}else{
			finished3 = true; 
		}

		finishedSending = finished3&&finished2&&finished1;
		wait(1, SC_NS); 
	}

}

void Server::timeRunning(){
	currentTime+=timeIncrement;

	for(int i = 0 ; i < numRobot; i++){
		if(!finishedSending){
			stopOrGo[i].write(0); 
		}
		else{
			robot_x[i] = x_in[i].read(); 
			// if(map[robot_grid[0]] - robot_x[0] < tolerateVal &&  map[robot_grid[0]] - robot_x[0] > tolerateVal-0.05) {
			if(map[robot_grid[i]] - robot_x[i] < tolerateVal && !prevStop[i] &&  map[robot_grid[i]] - robot_x[i] > tolerateVal-0.05) {
				if(!prevStop[i]){
					cout<<"At time: " <<currentTime<< " Server received request from robot "<<i<<endl;
					prevStop[i] = true; 
				}
				stopOrGo[i].write(0); 
			}

			else{
				if(prevStop[i]){
					cout<<"At time: " <<currentTime<< " Server permits robot "<<i <<" continues moving. "<<endl;
					prevStop[i] = false ; 
					robot_grid[i]++; 
				}
				stopOrGo[i].write(1); 
			}
		}
	}
	
}