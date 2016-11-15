#include "Robot.h"

void Robot::move(){
	if(stopOrGo_e && stopOrGo_s){
		x += robotSpeed * timeIncrement; 
		// cout<<"Robot Moving " << endl;
	} else{
		if(!stopOrGo_s)
			cout<<"At time: "<<currentTime<<" Robot is reaching the edge of the grid. Stop."<<endl;
		else if(!stopOrGo_e) 
			cout<<"At time: "<<currentTime<<". Obstacle is in the front. Stop."<<endl;
	}
}

void Robot::timeRunning(){
	while(true){
		// cout<<"Robot current time: " <<currentTime<<endl; 
		currentTime += timeIncrement;

		if(!isPathReceived){
			receivePath();
		}
		else{
			move(); 
			// testPathTransmission();

			stopOrGo_s = stopOrGo_server.read(); 
			stopOrGo_e = stopOrGo_env.read(); 

			// cout<<"current time: " << currentTime<<" Robot location: "<<x << endl;
			x_out_server.write(x); 
			x_out_env.write(x); 

		}

		wait(1, SC_NS); 
	} 
}

void Robot::testPathTransmission(){
		cout<<"Robot: ";

		for(int i = 0 ; i < numPath ; i++){
			cout<< path[i] << " " ;
		}

		cout<<endl; 		
}

void Robot::receivePath(){
	if(pathIndex < numPath){
		path[pathIndex]  = path_in.read(); 
		pathIndex++; 
	}else{
		isPathReceived = true;  
	}

}