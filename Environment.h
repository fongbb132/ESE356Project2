#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Environment: public sc_module{
public: 
	sc_fifo_in<sc_int<32>> x_in; 
	sc_fifo_in<sc_int<32>> y_in; 
	sc_fifo_out<bool> stopOrGo; //0 for stop 1 for go 

	SC_HAS_PROCESS(Environment); 

	Environment(sc_module_name name): sc_module(name){
	
	}

private:
	int path[numPath]; 
	
	
};
