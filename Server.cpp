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
	myfile.close(); 
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