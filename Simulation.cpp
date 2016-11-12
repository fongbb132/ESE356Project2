#include "Server.h"
#include "Environment.h"
#include "Robot.h"
#ifndef CONST_H
#define CONST_H 1
#include "const.h"
#endif
int sc_main(int argc, char* argv[]){
	Server server("server1"); 
	Environment environment("environment1");
	Robot robot("robot1"); 
	
	sc_fifo<sc_int<32>> robot_x; 
	sc_fifo<sc_int<32>> robot_y; 
	sc_fifo<sc_int<8>> path; 
	sc_fifo<bool> stopOrGo; 

	sc_clock clock("clock", 5, SC_NS); 

	robot.x_out(robot_x); 
	robot.y_out(robot_y); 
	robot.path_in(path); 
	robot.stopOrGo(stopOrGo);
	robot.clk(clock); 

	server.x_in(robot_x); 
	server.y_in(robot_y); 
	server.path_out(path); 
	server.clk(clock);

	environment.x_in(robot_x); 
	environment.y_in(robot_y); 
	environment.stopOrGo(stopOrGo); 


	server.loadPath(); 

	return 0;
}


