#include "Robot.h"

void Robot::move(){
	// cout<<currentTime<<sc_core::sc_get_current_process_b()->get_parent()->basename()<<" " <<stopOrGo_e << " " <<stopOrGo_s<<endl;
	if(stopOrGo_e && stopOrGo_s){
		x += robotSpeed * timeIncrement; 
		x_out_server.write(x); 
		x_out_env.write(x); 
		if(x - 1 > path[index]){
			index++; 
			// printf("%d %d ", index, path[index]);
			x = path[index]; 
		}
	} else{

		if(!stopOrGo_s && (prevStop_s != stopOrGo_s)){
		// 	cout<<"At time: "<<currentTime<<" " <<sc_core::sc_get_current_process_b()->get_parent()->basename()<<" is reaching the edge of the grid. Stop."<<endl;
			prevStop_s = stopOrGo_s;
		}
		if(!stopOrGo_e  && (prevStop_e != stopOrGo_e)) {//&& prevStop_e != stopOrGo_e  && (prevStop_e != stopOrGo_e)
		// 	cout<<"At time: "<<currentTime<<sc_core::sc_get_current_process_b()->get_parent()->basename()<<". Obstacle is in the front." <<"Robot Stops."<<endl;
			prevStop_e = stopOrGo_e;
		}
	}

	if(stopOrGo_s && (prevStop_s != stopOrGo_s)){
		// cout<<"At time: "<<currentTime<<sc_core::sc_get_current_process_b()->get_parent()->basename()<<" Robot is moving across the grid. "<<endl;
	}

	if(stopOrGo_e  && (prevStop_e != stopOrGo_e)){
		// cout<<"At time: "<<currentTime<<sc_core::sc_get_current_process_b()->get_parent()->basename()<<" Obstacle is passed. Robot continues moving. "<<endl;
	}
	if((prevStop_e != stopOrGo_e)){
		prevStop_e = stopOrGo_e;
	}

	if((prevStop_s != stopOrGo_s)){
		prevStop_s = stopOrGo_s;	
	}
}

void Robot::timeRunning(){
	currentTime += timeIncrement;

	if(!isPathReceived){
		// receivePath();
	}
	else{
		robotSpeed = speed_in.read(); 
		// printf("%f\n", robotSpeed);
		// testPathTransmission();
		// cout<<"******"<<endl;
		stopOrGo_s = stopOrGo_server.read(); 
		stopOrGo_e = stopOrGo_env.read(); 
		// index = index_in.read();
		// cout<<"*Robot reading env"<< stopOrGo_e<<endl;


		// cout<<"current time: " << currentTime<<" stopOrGo_e: "<<stopOrGo_e << endl;
		move(); 

		// cout<<"current time: " << currentTime<<" Robot location: "<<x << endl;
		
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
	while(true){
		if(pathIndex < numPath){
			path[pathIndex]  = path_in.read(); 
			pathIndex++; 
		}else{
			if(!init){
				init = true;
				x = path[0];
			}
			isPathReceived = true;  
		}
		wait(1, SC_NS); 
	}

}