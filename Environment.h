#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Environment: public sc_module{
public: 
	std::array<sc_in<float>, numRobot>  x_in; 
	std::array<sc_in<float>, numRobot> y_in; 
	std::array<sc_fifo_in<sc_int<32>>, numRobot> path_in;
	std::array<sc_out<bool>, numRobot> stopOrGo; //0 for stop 1 for go 
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
	int pathIndex[numRobot] ; 
	int path[numRobot][numPath]; 
	bool isPathReceived = false; 
	double robot_x[numRobot]; 

	double obstacle_x[numObstacle]; 
	double obstacle_y[numObstacle]; 
};
