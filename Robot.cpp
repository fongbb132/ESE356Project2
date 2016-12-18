#include "Robot.h"

void Robot::move(){
	if(stopOrGo_e && stopOrGo_s){
		x += robotSpeed * timeIncrement; 
		// cout<<"Robot Moving " << endl;
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
	// while(true){
		// cout<<"Robot current time: " <<currentTime<<endl; 
		currentTime += timeIncrement;

		if(!isPathReceived){
			// receivePath();
		}
		else{
			// testPathTransmission();
			// cout<<"******"<<endl;
			stopOrGo_s = stopOrGo_server.read(); 
			stopOrGo_e = stopOrGo_env.read(); 
			// cout<<"*Robot reading env"<< stopOrGo_e<<endl;


			// cout<<"current time: " << currentTime<<" stopOrGo_e: "<<stopOrGo_e << endl;
			move(); 

			// cout<<"current time: " << currentTime<<" Robot location: "<<x << endl;
			x_out_server.write(x); 
			x_out_env.write(x); 

		}

		// wait(1, SC_NS); 
	// } 
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
			isPathReceived = true;  
		}
		wait(1, SC_NS); 
	}

}