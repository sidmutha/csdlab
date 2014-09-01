#include"wrapper.h"

Wrapper::Wrapper(int numCaches){
  cacheArray = new Cache[numCaches];
  ramID = numCaches;
}

void Wrapper::read(int address){
  cacheArray[0].read(address);
}

void Wrapper::write(int address){
  cacheArray[0].write(address);
}

