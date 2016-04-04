CXX=g++
RM= rm -rf
CXX_FLAGS= -c -g -Wall -I$(SYSTEMC)/include

LD_FLAGS= -L$(SYSTEMC)/lib-$(TARGET_ARCH) -lsystemc

SRCS_CXX= basic.cpp

OBJS_CXX= $(SRCS_CXX:.cpp=.o)

PROJECT=01_SystemCTest

all: $(PROJECT)
	./$(PROJECT)

$(PROJECT): $(OBJS_CXX)
	$(CXX) -o $@ $< $(LD_FLAGS)

.cpp.o:
	$(CXX) $(CXX_FLAGS) $< -o $@

clean:
	$(RM) $(OBJS_CXX) $(PROJECT)
