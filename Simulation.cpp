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
	
	std::vector<Robot*> robots; 
	
	std::array<sc_signal<float>, numRobot> robot_loc_server; 
	std::array<sc_signal<float>, numRobot> robot_y_server; 

	std::array<sc_signal<float>, numRobot> robot_loc_env; 
	std::array<sc_signal<float>, numRobot> robot_y_env; 

	std::array<sc_fifo<sc_int<32>>, numRobot> path_env; 

	std::array<sc_fifo<sc_int<32>>, numRobot> path_robot; 
	
	std::array<sc_signal<bool>, numRobot> stopOrGo_env; 
	std::array<sc_signal<bool>, numRobot> stopOrGo_server; 
	std::array<sc_signal<double>, numRobot> path_index; 


	sc_clock clock("clock", 1, SC_NS); 

	for(int i = 0 ; i < numRobot; i++){
		std::ostringstream oss; 
		oss<<"robot"<<i; 
		Robot* tempRobot = new Robot(oss.str().c_str());
		robots.push_back(tempRobot);

		robots[i]->x_out_server(robot_loc_server[i]); 
		robots[i]->y_out_server(robot_y_server[i]); 
		robots[i]->x_out_env(robot_loc_env[i]); 
		robots[i]->y_out_env(robot_y_env[i]); 
		robots[i]->path_in(path_robot[i]); 
		robots[i]->stopOrGo_env(stopOrGo_env[i]);
		robots[i]->stopOrGo_server(stopOrGo_server[i]);
		robots[i]->index_in(path_index[i]);
		robots[i]->clk(clock); 


		server.x_in[i](robot_loc_server[i]); 
		server.index_out[i](path_index[i]); 
		server.y_in[i](robot_y_server[i]); 
		server.path_out_robot[i](path_robot[i]); 
		server.path_out_env[i](path_env[i]);
		server.stopOrGo[i](stopOrGo_server[i]);

		environment.path_in[i](path_env[i]); 
		environment.x_in[i](robot_loc_env[i]); 
		environment.y_in[i](robot_y_env[i]); 
		environment.stopOrGo[i](stopOrGo_env[i]); 
	}

	server.clk(clock);
	environment.clk(clock);

	server.loadPath(); 

	// sc_trace_file *wf = sc_create_vcd_trace_file("waveform"); 
	// sc_trace(wf, path.read(), "Path_comm");
	sc_start(10000, SC_NS); 
	// sc_close_vcd_trace_file(wf); 
	return 0;
}


