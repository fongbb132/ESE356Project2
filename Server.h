#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif

class Server: public sc_module{
public: 
	std::array<sc_in<float>, numRobot> x_in; 
	std::array<sc_in<float>, numRobot> y_in; 
	std::array<sc_out<bool>, numRobot> stopOrGo; 
	std::array<sc_fifo_out<sc_int<8>>, numRobot> path_out_robot; 
	std::array<sc_fifo_out<sc_int<8>>, numRobot> path_out_env; 
	sc_in<bool> clk; 

	void loadPath(); 
	void sendPath(); 
	void timeRunning(); 
	void testPathTransmission(); 

	int map[numGrid]; 
	int path[numPath]; 

	SC_HAS_PROCESS(Server); 

	Server(sc_module_name name): sc_module(name){
		// for(int i = 0 ; i < numRobot; i++){
		// 	x_in[i] = new sc_in<float>(); 
		// 	y_in[i] = new sc_in<float>(); 

		// 	stopOrGo = new sc_out<bool>(); 
		// 	path_out_env = new sc_fifo_out<sc_int<8>>(); 
		// 	path_out_robot = new sc_fifo_out<sc_int<8>>(); 

		// }

		for(int i = 0; i < numRobot ; i++){
			robot_grid[i] = 0; 
			robot_x[i] = 0; 
			prevStop[i] = false; 
		}
		SC_THREAD(sendPath);
		SC_METHOD(timeRunning); 
		sensitive<<clk.pos();
	}

private:
	double currentTime = 0.0;
	int pathIndex = 0; 
	bool finishedSending = false; 
	double robot_x[numRobot]; 
	int robot_grid[numRobot];//path[0]; 

	bool prevStop[numRobot]; 
};



