#ifndef _CACHE_H
#define _CACHE_H

#include"wrapper.h"
#include<cstdint>
#include<iostream>
#include<string>

struct CacheEntry{
  int set, way;
  uint64_t tag;
  int freq;
  bool lru;
  bool dirty;
   int state;
};

class Wrapper;

class Cache{
 public:
  CacheEntry** cache;
  
  int numSets;
  int numWays;
  int replacementPolicy;
  int id;
  int offsetBits;
  
int setBits;
int tagBits;  

Wrapper* wrapper;
  
  Cache(int id, Wrapper* w, int size, int associativity, int blockSize, int replacementPolicy);
  
  Cache();
  void read(uint64_t address);
  void write(uint64_t address);
  
  int getVictim(int set);
  
  int getSet(uint64_t address);
  uint64_t getTag(uint64_t address);
uint64_t generatePseudoAddress(int set, uint64_t tag);
int findTagInSet(uint64_t tag, int set); 
  
  // do we really need these?
  void get(uint64_t address);
  void put(uint64_t address);
  
  int readHits;
  int readMisses;
  int writeHits;
  int writeMisses;
};

#endif
