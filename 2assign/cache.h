#ifndef _CACHE_H
#define _CACHE_H

#include<iostream>
#include<string>

struct CacheEntry{
  int set, way;
  int tag;
  int freq;
  bool lru;
  bool dirty;
};


class Cache{
  CacheEntry** cache;
  
  int numSets;
  int numWays;
  int replacementPolicy;
  int id;
  
  Cache(int id, Wrapper* wrapper, int size, int associativity, int blockSize, int replacementPolicy);
  void read(int address);
  void write(int address);
  
  int getVictim(int set);
  
  int getSet(int address);
  int getTag(int address);
  int generatePseudoAddress(int set, int tag);
  int findTagInSet(int tagx, int set); 
  
  // do we really need these?
  void get(int address);
  void put(int address);
  
  int readHits;
  int readMisses;
  int writeHits;
  int writeMisses;
};

#endif
