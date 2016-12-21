#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Robot: public sc_module{
public: 
	sc_out<float> x_out_server; 
	sc_out<float> y_out_server; 

	sc_out<float> x_out_env; 
	sc_out<float> y_out_env;

	sc_fifo_in<sc_int<32>> path_in;
	sc_in<bool> stopOrGo_env; //0 for stop 1 for go 
	sc_in<bool> stopOrGo_server; 
	sc_in<bool> clk; 
	sc_in<double> index_in; 
	sc_in<double> speed_in; 

	SC_HAS_PROCESS(Robot); 

	void move(); 
	void timeRunning(); 
	void receivePath(); 
	void testPathTransmission(); 

	Robot(sc_module_name name): sc_module(name){
		SC_THREAD(receivePath);
		SC_METHOD(timeRunning); 
		sensitive<<clk.pos();
	}

private:
	bool init = false;
	int index = 0 ; 
	double currentTime = 0.0; 
	int pathIndex = 0 ; 
	int path[numPath]; 
	bool isPathReceived = false; 
	float x = 0.0; 
	bool stopOrGo_s = true, stopOrGo_e = true; 
	bool prevStop_s = true, prevStop_e = true; 
 	double robotSpeed = 2.0; 
};
