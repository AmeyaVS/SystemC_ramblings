CXX= g++

CXX_FLAGS= -c -g -Wall -I. -I$(SYSTEMC)/include

SRCS_CXX= timer.cpp

OBJS_CXX= $(SRCS_CXX:.cpp=.o)

PROJECT= 04_timertest

SC_TRACE_FILE= timer

all: $(PROJECT)
	./$(PROJECT)
	@make cmp_result
	vcd_hier_manip $(SC_TRACE_FILE).vcd

$(PROJECT): $(OBJS_CXX)
	$(CXX) $^ -L. -L$(SYSTEMC)/lib-$(TARGET_ARCH) -o $@ -lsystemc

.cpp.o:
	$(CXX) $(CXX_FLAGS) -DSC_TRACE_FILE=\"$(SC_TRACE_FILE)\" $< -o $@

clean:
	$(RM) $(OBJS_CXX) $(PROJECT) *.dat *.vcd

# The cmp_result target compares the simulation results with the
# golden results. The testbench writes out the results file (output.dat)
# in the simulation configuration directory. The cmp_result target is
# automatically run at the end of each simulation.

GOLD_DIR= ./golden
GOLD_FILE= $(GOLD_DIR)/ref_output.dat

cmp_result:
	@echo "****************************"
	@if diff -w $(GOLD_FILE) ./output.dat ; then \
		echo "SIMULATION PASSED"; \
	else \
		echo "SIMULATION FAILED"; \
	fi
	@echo "****************************"
