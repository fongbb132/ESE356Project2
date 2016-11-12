#include "systemc.h"
#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Server: public sc_module{
public: 
	sc_fifo_in<sc_int<32>> x_in; 
	sc_fifo_in<sc_int<32>> y_in; 
	sc_fifo_out<sc_int<8>>path_out; 
	sc_in<bool> clk; 

	void loadPath(); 
	void sendPath(); 
	void timeRunning(); 

	int map[numGrid]; 
	int path[numPath]; 


	SC_HAS_PROCESS(Server); 

	Server(sc_module_name name): sc_module(name){
		SC_THREAD(timeRunning); 
	}

private:
	double currentTime = 0.0;
	int pathIndex = 0; 
	
};



