CXX= g++

CXX_FLAGS= -c -g -Wall -I. -I$(SYSTEMC)/include

SRCS_CXX= fir.cpp tb.cpp firsytemmain.cpp

OBJS_CXX= $(SRCS_CXX:.cpp=.o)

PROJECT= 03_firtest

all: $(PROJECT)
	./$(PROJECT)
	@make cmp_result

$(PROJECT): $(OBJS_CXX)
	$(CXX) $^ -L. -L$(SYSTEMC)/lib-$(TARGET_ARCH) -o $@ -lsystemc

.cpp.o:
	$(CXX) $(CXX_FLAGS) $< -o $@

clean:
	$(RM) $(OBJS_CXX) $(PROJECT) *.dat

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
