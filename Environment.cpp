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

	// while(true){
		// cout<<"Environment current time: " <<currentTime<<endl; 
		currentTime+=timeIncrement;
		// stopOrGo.write(1); 
		if(!isPathReceived){
			// receivePath();
			obstacle_x = 20;
			stopOrGo.write(1); 
		}
		else{
			obstacle_x -= obstacleSpeed * timeIncrement; 

			// cout<<"Environment at time: "<< currentTime << " robot_x " << robot_x<<" obstacle_x: " << obstacle_x<<endl;
			robot_x =  x_in.read(); 

			if(abs(robot_x - obstacle_x )< 0.005 && abs(robot_x - obstacle_x )> 0){
				stopOrGo.write(0); 
				// cout<<" Env writing 0 " <<endl ;
			}else{
				stopOrGo.write(1); 
				// cout<<" Env writing 1 " <<endl ;
			}

			// cout<<"environment time: " << currentTime << " x: " <<robot_x<<endl; 

			// testPathTransmission();
		}

	// } 
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














