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
	if(pathIndex < numPath){
		// cout<<"Server " << path[pathIndex]<< " " <<endl; 
		path_out_env.write(path[pathIndex]);
		path_out_robot.write(path[pathIndex]);
		pathIndex++; 
		if(pathIndex == numPath){
			
		}
	}
	wait(1, SC_NS); 
}


void Server::timeRunning(){
	while(true){
		// cout<<"Server current time: " <<currentTime<<endl; 
		currentTime+=timeIncrement;
		sendPath(); 

		stopOrGo.write(1); 
	}

}