#include "Environment.h"

//to test whether the path is transmitted successfully
void Environment::testPathTransmission(){
	cout<<"Environment: ";
	for(int i = 0 ; i < numPath ; i++){
		cout<< path[i] << " " ;
	}
	cout<<endl; 
}

void Environment::timeRunning(){
	currentTime+=timeIncrement;
	if(!isPathReceived){
		obstacle_x = 20;
		stopOrGo.write(1); 
	}
	else{
		obstacle_x -= obstacleSpeed * timeIncrement; 
		robot_x =  x_in.read();             
		if(abs(robot_x - obstacle_x )< 0.005 && abs(robot_x - obstacle_x )> 0){
			stopOrGo.write(0); 
		}else{
			stopOrGo.write(1); 
		}
	}
}

void Environment::receivePath(){
	while(true){
		if(pathIndex < numPath){
			path[pathIndex]  = path_in.read(); 
			pathIndex++; 
		}else{
			isPathReceived = true; 
		}
		wait(1, SC_NS); 
	}
}














