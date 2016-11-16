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
			path_out_env.write(path[pathIndex]);
			path_out_robot.write(path[pathIndex++]);
		}else{
			finishedSending = true;
		}
		wait(1, SC_NS); 
	}
}


void Server::timeRunning(){
	currentTime+=timeIncrement;
	if(!finishedSending){
		stopOrGo.write(1); 
	}
	else{
		robot_x = x_in.read(); 

		if(map[robot_grid] - robot_x < tolerateVal && !prevStop &&  map[robot_grid] - robot_x > tolerateVal-0.05) {
			if(!prevStop){
				cout<<"At time: " <<currentTime<< " Server received request from robot. "<<endl;
				prevStop = true; 
			}
			stopOrGo.write(0); 
		}
		else{
			if(prevStop){
				cout<<"At time: " <<currentTime<< " Server permits robot continues moving. "<<endl;
				prevStop = false ; 
				robot_grid++; 
			}
			stopOrGo.write(1); 
		}
	}
}