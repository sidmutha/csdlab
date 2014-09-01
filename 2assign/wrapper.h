#include"cache.h"

class Wrapper{
  Cache* cacheArray;
  int ramID;
  
  void read(int address);
  void write(int address);
  Wrapper(int numCaches);
};
