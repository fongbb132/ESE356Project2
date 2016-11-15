#include "systemc.h"
#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Robot: public sc_module{
public: 
	sc_fifo_out<float> x_out_server; 
	sc_fifo_out<float> y_out_server; 

	sc_fifo_out<float> x_out_env; 
	sc_fifo_out<float> y_out_env;

	sc_fifo_in<sc_int<8>> path_in;
	sc_fifo_in<bool> stopOrGo_env; //0 for stop 1 for go 
	sc_fifo_in<bool> stopOrGo_server; 
	sc_in<bool> clk; 


	SC_HAS_PROCESS(Robot); 

	void move(); 
	void timeRunning(); 
	void receivePath(); 
	void testPathTransmission(); 

	Robot(sc_module_name name): sc_module(name){
		SC_THREAD(timeRunning); 
	}


private:
	double currentTime = 0.0; 
	int pathIndex = 0 ; 
	int path[numPath]; 
	bool isPathReceived = false; 
	float x = 0.0; 
};
