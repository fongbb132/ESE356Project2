#include "systemc.h"

#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif


#ifndef PAIR_H
#define PAIR_H 1
#include "pair.h"
#endif
class Server: public sc_module{
public: 
	std::array<sc_in<float>, numRobot> x_in; 
	std::array<sc_in<float>, numRobot> y_in; 
	std::array<sc_out<bool>, numRobot> stopOrGo; 
	std::array<sc_fifo_out<sc_int<32>>, numRobot> path_out_robot; 
	std::array<sc_fifo_out<sc_int<32>>, numRobot> path_out_env; 
	std::vector<int> nodes;
	sc_in<bool> clk; 
	std::array<sc_out<double>, numRobot> index_out; 

	void loadPath(); 
	void sendPath(); 
	void timeRunning(); 
	void testPathTransmission(); 
	void nodeOrdering(); 

	int map[numGrid]; 

	int map_2d[numRow][numCol];
	std::vector<std::vector<int>> path;

	SC_HAS_PROCESS(Server); 

	Server(sc_module_name name): sc_module(name){

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
	std::map<int, loc*> map_loc;
	double currentTime = 0.0;
	int pathIndex = 0; 
	bool finishedSending = false; 
	double robot_x[numRobot]; 
	int robot_grid[numRobot];//path[0]; 
	int prevLoc[numRobot];
	int indexes[numRobot];
	bool prevStop[numRobot]; 
};



