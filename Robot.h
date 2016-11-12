#include "systemc.h"
#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Robot: public sc_module{
public: 
	sc_fifo_out<sc_int<32>> x_out; 
	sc_fifo_out<sc_int<32>> y_out; 
	sc_fifo_in<sc_int<8>> path_in;
	sc_fifo_in<bool> stopOrGo; //0 for stop 1 for go 
	sc_in<bool> clk; 


	SC_HAS_PROCESS(Robot); 

	void move(); 
	void timeRunning(); 
	void receivePath(); 

	Robot(sc_module_name name): sc_module(name){
		SC_METHOD(timeRunning); 
		sensitive<<clk.pos(); 
	}


private:
	double currentTime = 0.0; 
	int pathIndex = 0 ; 
};
