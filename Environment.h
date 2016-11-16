#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Environment: public sc_module{
public: 
	sc_in<float> x_in; 
	sc_in<float> y_in; 
	sc_fifo_in<sc_int<8>> path_in;
	sc_out<bool> stopOrGo; //0 for stop 1 for go 
	sc_in<bool> clk;

	SC_HAS_PROCESS(Environment);

	void timeRunning();  
	void receivePath(); 
	void testPathTransmission(); 

	Environment(sc_module_name name): sc_module(name){
		SC_THREAD(receivePath);
		
		SC_METHOD(timeRunning);
		sensitive<<clk.pos();
	
	}

private:
	double currentTime = 0.0; 
	int pathIndex = 0 ; 
	int path[numPath]; 
	bool isPathReceived = false; 
	double robot_x; 

	double obstacle_x = 30; 
};
