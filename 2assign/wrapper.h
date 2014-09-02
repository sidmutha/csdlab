#ifndef _WRAPPER_H
#define _WRAPPER_H

#include"cache.h"
#include<cstdint>
class Cache;

class Wrapper{
 public: 
  Cache* cacheArray;
  int ramID;
  Wrapper(int numCaches);
  void read(uint64_t address);
  void write(uint64_t address);  
};
#endif
