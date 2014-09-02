FLAGS = -g --std=c++11

all: sim

sim: cachesim.o wrapper.o cache.o
	g++ $(FLAGS) -o sim cachesim.o wrapper.o cache.o

cachesim.o: cachesim.cpp wrapper.h cache.h
	g++ $(FLAGS) -c cachesim.cpp

wrapper.o: wrapper.cpp wrapper.h cache.h
	g++ $(FLAGS) -c wrapper.cpp

cache.o: cache.cpp cache.h wrapper.h
	g++ $(FLAGS) -c cache.cpp 

clean: 
	rm -rf sim *.o 
