#include "Server.h"
#include <fstream> 
void Server::loadPath(){
	ifstream myfile; 
	myfile.open("input.txt"); 
	for(int i = 0; i < numGrid; i++){
		myfile>>map[i];
	}
	for(int i = 0; i < numPath; i++){
		myfile>>paths[i];
	}
	myfile.close(); 


	// for(int i = 0 ; i < numGrid; i++){
	// 	cout<< map[i] << " " ; 
	// }

	// cout<<endl ; 
	// for(int i = 0 ; i < numPath; i++){
	// 	cout<< paths[i] <<" " ; 
	// }
	// cout<<endl;
}


void Server::sendPath(){
	if(clk.read() && pathIndex < numPath){
		path_out.write(pathIndex);
		pathIndex++; 
	}
}


void Server::timeRunning(){
	currentTime+=0.001;
}