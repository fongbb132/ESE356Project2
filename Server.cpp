#include "Server.h"
#include <fstream> 
void Server::loadPath(){
	ifstream myfile; 
	myfile.open("input.txt"); 
	for(int i = 0; i < numGrid; i++){
		myfile>>map[i];
	}
	for(int i = 0; i < numPath; i++){
		myfile>>path[i];
	}

	for(int i = 0; i < numRow ; i++){
		for(int j = 0 ; j < numCol; j++){
			map_2d[i][j]=0; 
		}
	}
	int numSquare;
	myfile>>numSquare; 
	for(int i = 0 ; i < numSquare ; i++){
		int lowX, lowY, highX, highY; 

		myfile>>lowX>>lowY>>highX>>highY; 

		for(int i = lowX ; i<highX; i++){
			for(int j = lowY; j<highY; j++){
				map_2d[j][i] = 1;
			}
		}
	}
	myfile.close(); 


	for(int i = 0; i < numRow ; i++){
		for(int j = 0 ; j < numCol; j++){
			cout<< map_2d[i][j]<<"|"; 
		}
		cout<<endl;
	}
}


void Server::sendPath(){
	while(true){
		if(pathIndex < numPath){
			path_out_env[0].write(path[pathIndex]);
			path_out_robot[0].write(path[pathIndex++]);
		}else{
			finishedSending = true;
		}
		wait(1, SC_NS); 
	}
}

void Server::timeRunning(){
	currentTime+=timeIncrement;
	if(!finishedSending){
		stopOrGo[0].write(1); 
	}
	else{
		robot_x[0] = x_in[0].read(); 
		// if(map[robot_grid[0]] - robot_x[0] < tolerateVal &&  map[robot_grid[0]] - robot_x[0] > tolerateVal-0.05) {
		if(map[robot_grid[0]] - robot_x[0] < tolerateVal && !prevStop[0] &&  map[robot_grid[0]] - robot_x[0] > tolerateVal-0.05) {
			if(!prevStop[0]){
				cout<<"At time: " <<currentTime<< " Server received request from robot. "<<endl;
				prevStop[0] = true; 
			}
			stopOrGo[0].write(0); 
		}

		else{
			if(prevStop[0]){
				cout<<"At time: " <<currentTime<< " Server permits robot continues moving. "<<endl;
				prevStop[0] = false ; 
				robot_grid[0]++; 
			}
			stopOrGo[0].write(1); 
		}
	}
}