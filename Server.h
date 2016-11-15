#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Server: public sc_module{
public: 
	sc_in<float> x_in; 
	sc_in<float> y_in; 
	sc_out<bool> stopOrGo; 
	sc_fifo_out<sc_int<8>>path_out_robot; 
	sc_fifo_out<sc_int<8>>path_out_env; 
	sc_in<bool> clk; 

	void loadPath(); 
	void sendPath(); 
	void timeRunning(); 
	void testPathTransmission(); 

	int map[numGrid]; 
	int path[numPath]; 

	SC_HAS_PROCESS(Server); 

	Server(sc_module_name name): sc_module(name){

		SC_THREAD(sendPath);
		SC_METHOD(timeRunning); 
		sensitive<<clk.pos();
	}

private:
	double currentTime = 0.0;
	int pathIndex = 0; 
	bool finishedSending = false; 
	double robot_x = 0; 
	int robot_grid = 0;//path[0]; 

	bool prevStop = false; 
};



