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

	while(true){
		// cout<<"Environment current time: " <<currentTime<<endl; 
		currentTime+=0.001;
		if(!isPathReceived)
			receivePath();
		else{


			cout<<x_in.read()<<endl; 


			// testPathTransmission();
		}
		stopOrGo.write(1); 

		wait(1, SC_NS); 
	} 
}

void Environment::receivePath(){
	if(pathIndex < numPath){
		path[pathIndex]  = path_in.read(); 
		pathIndex++; 
	}else{
		isPathReceived = true; 
	}

}














