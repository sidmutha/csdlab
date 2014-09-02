#include"wrapper.h"

Wrapper::Wrapper(int numCaches){
  cacheArray = new Cache[numCaches];
  ramID = numCaches;
}

void Wrapper::read(uint64_t address){
  cacheArray[0].read(address);
}

void Wrapper::write(uint64_t address){
  cacheArray[0].write(address);
}


