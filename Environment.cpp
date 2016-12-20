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

	for(int i = 0 ; i < numRobot ; i++){
		if(!isPathReceived){
			obstacle_x[i] = 20;
			stopOrGo[i].write(1); 
		}
		else{
			obstacle_x[i] -= obstacleSpeed * timeIncrement; 
			robot_x[i] =  x_in[i].read();             
			if(abs(robot_x[i]- obstacle_x[i] )< 0.005 && abs(robot_x[i] - obstacle_x[i] )> 0){
				stopOrGo[i].write(0); 
			}else{
				stopOrGo[i].write(1); 
			}
		}
	}
}

void Environment::receivePath(){
	while(true){
		for(int i = 0 ; i < numRobot; i++){
			if(pathIndex[i] < numPath){
				path[i][pathIndex[i]]  = path_in[i].read(); 
				pathIndex[i]++; 
			}else{
				isPathReceived = true; 
			}
		}
		wait(1, SC_NS); 
	}
}














