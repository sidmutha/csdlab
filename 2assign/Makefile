FLAGS = -g --std=c++11

all: pinatrace

sim: cachesim.o wrapper.o cache.o
	g++ $(FLAGS) -o sim cachesim.o wrapper.o cache.o

pinatrace: pinatrace.cpp wrapper.o cache.o
	g++ -g -std=c++11 -DBIGARRAY_MULTIPLIER=1 -Wall -Werror -Wno-unknown-pragmas -fno-stack-protector -DTARGET_IA32E -DHOST_IA32E -fPIC -DTARGET_LINUX  -I./pin/source/include/pin -I./pin/source/include/pin/gen -I./pin/extras/components/include -I./pin/extras/xed2-intel64/include -I./pin/source/tools/InstLib -O3 -fomit-frame-pointer -fno-strict-aliasing   -c -o pinatrace.o  pinatrace.cpp
	g++ -shared -Wl,--hash-style=sysv -Wl,-Bsymbolic -Wl,--version-script=./pin/source/include/pin/pintool.ver    -o pinatrace.so pinatrace.o wrapper.o cache.o -L./pin/intel64/lib -L./pin/intel64/lib-ext -L./pin/intel64/runtime/glibc -L./pin/extras/xed2-intel64/lib -lpin -lxed -ldwarf -lelf -ldl


cachesim.o: cachesim.cpp wrapper.h cache.h
	g++ $(FLAGS) -c cachesim.cpp

wrapper.o: wrapper.cpp wrapper.h cache.h
	g++ $(FLAGS) -fPIC -c wrapper.cpp

cache.o: cache.cpp cache.h wrapper.h
	g++ $(FLAGS) -fPIC -c cache.cpp 

clean: 
	rm -rf sim *.o 
