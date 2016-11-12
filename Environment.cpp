#include "Environment.h"


void Environment::timeRunning(){

	while(true){
		currentTime+=0.001;
		if(!isPathReceived)
			receivePath();
		else{

		}

		wait(1, SC_NS); 
	} 
}

void Environment::receivePath(){
	if(pathIndex < numPath){
		path[pathIndex]  = path_in.read(); 
		cout<<"Environment " << path[pathIndex]<<endl ; 

		pathIndex++; 
	}else{
		isPathReceived = true; 
	}

}