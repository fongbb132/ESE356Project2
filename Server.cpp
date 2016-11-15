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
		path_out_robot.write(path[pathIndex++]);
		// stopOrGo.write(0); 
	}else{
		finishedSending = true;
	}
}


void Server::timeRunning(){
	while(true){
		stopOrGo.write(1); 
		// cout<<"Server current time: " <<currentTime<<endl; 
		currentTime+=timeIncrement;
		if(!finishedSending){
			// cout<<"Current Time: "<<currentTime<<" Not finishedSending"<<endl;
			sendPath(); 
		}
		else{
			robot_x = x_in.read(); 
			cout<<"Server time: "<<currentTime<< " x " << robot_x<<endl ; 
		}
		wait(1, SC_NS); 
	}
}