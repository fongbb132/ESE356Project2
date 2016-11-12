#include "Robot.h"

void Robot::move(){

}


void Robot::timeRunning(){

	while(true){
		currentTime+=0.001;
		if(!isPathReceived)
			receivePath();
		else{

		}

		wait(1, SC_NS); 
	} 
}

void Robot::receivePath(){
	if(pathIndex < numPath){
		path[pathIndex]  = path_in.read(); 
		cout<<"Robot " << path[pathIndex]<<endl ; 

		pathIndex++; 
	}else{
		isPathReceived = true; 
	}

}