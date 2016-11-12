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
		cout<<"Server " << path[pathIndex]<< " " <<endl; 
		path_out.write(path[pathIndex]);
		pathIndex++; 
	}
	wait(1, SC_NS); 
}


void Server::timeRunning(){
	while(true){
		currentTime+=0.001;
		sendPath(); 
	}
}