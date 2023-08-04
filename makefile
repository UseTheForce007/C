CXXFLAGS := -std=c++11 -Wall -Wextra -pedantic -I ./eigen-3.4.0/
CXX := clang++	
CXXDEBUGFLAGS := $(CXXFLAGS) -g
CXXRELEASEFLAGS := $(CXXFLAGS) -O3

SRC := $(wildcard *.cpp)

debug: 
	$(CXX) $(CXXDEBUGFLAGS) $(SRC) -o main.o 
release:
	$(CXX) $(CXXRELEASEFLAGS) $(SRC) -o main.o