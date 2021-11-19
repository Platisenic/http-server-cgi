CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -pthread -lboost_system
CXX_INCLUDE_DIRS=/usr/local/include
CXX_INCLUDE_PARAMS=$(addprefix -I , $(CXX_INCLUDE_DIRS))
CXX_LIB_DIRS=/usr/local/lib
CXX_LIB_PARAMS=$(addprefix -L , $(CXX_LIB_DIRS))
EXEC = http_server

.PHONY: all clean prepare

all: $(EXEC)

$(EXEC): $(EXEC).cpp
	$(CXX) $< -o $@ $(CXX_INCLUDE_PARAMS) $(CXX_LIB_PARAMS) $(CXXFLAGS)

clean:
	rm -f $(EXEC)

run: $(EXEC)
	./$(EXEC) 3333

prepare:
	mkdir -p bin
	cp `which ls` bin/ls
	cp `which cat` bin/cat
	g++ commands/noop.cpp -o bin/noop
	g++ commands/number.cpp -o bin/number
	g++ commands/removetag0.cpp -o bin/removetag0
	g++ commands/removetag.cpp -o bin/removetag
	g++ commands/delayedremovetag.cpp -o bin/delayedremovetag
