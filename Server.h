#include "systemc.h"
#include <stdio.h>
#include <algorithm>
#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


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
	std::array<sc_out<double>, numRobot> speed_out; 
	bool isFirstTime = true; 
	double dist1 = 0 ; 
	double dist2 = 0 ; 
	double dist3 = 0; 
	double dist1C = 0 ; 
	double dist2C = 0 ; 
	double dist3C = 0; 
	int randomIndex = 0 ; 
	double randomNum[80]; 
	double randomStart[80]; 
	int robotSelect[80]; 
	double randomS[3]; 

	void loadPath(); 
	void sendPath(); 
	void timeRunning(); 
	void testPathTransmission(); 
	void nodeOrdering(); 
	void calculateSpeed();
	void changePath();
	
	std::map<int, numList *>ranks;

	int map_2d[numRow][numCol];
	std::vector<std::vector<int>> path;

	SC_HAS_PROCESS(Server); 

	Server(sc_module_name name): sc_module(name){

		for(int i = 0; i < numRobot ; i++){
			robot_grid[i] = 0; 
			robot_x[i] = 0; 
			prevStop[i] = false; 
			speed[i] = 2.0; 
		}
		SC_THREAD(sendPath);
		SC_METHOD(timeRunning); 
		sensitive<<clk.pos();
  		srand (time(NULL));
		for(int i = 0; i < 80; i++){
			randomNum[i]  = (double)rand() /RAND_MAX*0.1;
			randomStart[i] = (double) rand() /RAND_MAX*13+2; 
			robotSelect[i] = (int)rand()%3; 
		}
		for(int i = 0 ; i < 3; i++){
			randomS[i] = (double)rand()/RAND_MAX *6; 
			printf("%s %f\n", "Robot start", randomS[i] );
		}
		std::sort(randomStart , randomStart+80); 
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
	std::map<int, int> time_map; 
	double speed[numRobot]; 
	double time1 = 0 , time2 = 0, time3 = 0; 
	std::map<int, pairList*> map;

	

};



