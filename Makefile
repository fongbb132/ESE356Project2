SYSTEMC_HOME    = /usr/local/systemc-2.3.1
TARGET_ARCH     = macosx64

SYSTEMC_BUS_DIR = $(SYSTEMC_HOME)/simple_bus
SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

# LIBTOOL Setting

GXX             = g++ -std=c++11 
GCC             = gcc
LD              = g++

FLAGS           = -g -pedantic -Wno-long-long -w \
                 -DSC_INCLUDE_DYNAMIC_PROCESSES -fpermissive \
                 -I$(SYSTEMC_INC_DIR) 
LDFLAGS         = -L. -L$(SYSTEMC_LIB_DIR) -lsystemc -lm

SRCS = Simulation.cpp Robot.cpp Environment.cpp Server.cpp
OBJS=$(SRCS:.cpp=.o)

# main
main: $(OBJS)
	$(GXX) -o $@ $(OBJS) $(LDFLAGS) 

.cpp.o:
	$(GXX) -I$(SYSTEMC_INC_DIR) -c $< $(LDFLAGS) 

clean:
	rm -f main *.o *.lo 
	rm -rf .libs