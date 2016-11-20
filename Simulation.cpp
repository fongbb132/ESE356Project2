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
	
	sc_signal<float> robot_x_server; 
	sc_signal<float> robot_y_server; 

	sc_signal<float> robot_x_env; 
	sc_signal<float> robot_y_env; 

	sc_fifo<sc_int<8>> path_env; 

	sc_fifo<sc_int<8>> path_robot; 
	
	sc_signal<bool> stopOrGo_env; 
	sc_signal<bool> stopOrGo_server; 


	sc_clock clock("clock", 1, SC_NS); 

	robot.x_out_server(robot_x_server); 
	robot.y_out_server(robot_y_server); 
	robot.x_out_env(robot_x_env); 
	robot.y_out_env(robot_y_env); 
	robot.path_in(path_robot); 
	robot.stopOrGo_env(stopOrGo_env);
	robot.stopOrGo_server(stopOrGo_server);
	robot.clk(clock); 

	server.x_in[0](robot_x_server); 
	server.y_in[0](robot_y_server); 
	server.path_out_robot[0](path_robot); 
	server.path_out_env[0](path_env);
	server.clk(clock);
	server.stopOrGo[0](stopOrGo_server);

	environment.x_in[0](robot_x_env); 
	environment.y_in[0](robot_y_env); 
	environment.path_in[0](path_env); 
	environment.stopOrGo[0](stopOrGo_env); 
	environment.clk(clock);

	server.loadPath(); 

	// sc_trace_file *wf = sc_create_vcd_trace_file("waveform"); 
	// sc_trace(wf, path.read(), "Path_comm");
	sc_start(10000, SC_NS); 
	// sc_close_vcd_trace_file(wf); 
	return 0;
}


