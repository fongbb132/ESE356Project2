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
		obstacle_x[0] = 20;
		stopOrGo[0].write(1); 
	}
	else{
		obstacle_x[0] -= obstacleSpeed * timeIncrement; 
		robot_x[0] =  x_in[0].read();             
		if(abs(robot_x[0]- obstacle_x[0] )< 0.005 && abs(robot_x[0] - obstacle_x[0] )> 0){
			stopOrGo[0].write(0); 
		}else{
			stopOrGo[0].write(1); 
		}
	}
}

void Environment::receivePath(){
	while(true){
		if(pathIndex[0] < numPath){
			path[pathIndex[0]]  = path_in[0].read(); 
			pathIndex[0]++; 
		}else{
			isPathReceived = true; 
		}
		wait(1, SC_NS); 
	}
}














