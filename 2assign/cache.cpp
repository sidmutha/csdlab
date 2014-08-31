#include"cache.h"

Cache::Cache(int size, int associativity, int blockSize, int replacementPolicy){
  numSets = size * 1024 / (associativity * blockSize);
  numWays = associativity;
  cache = new CacheEntry*[numSets];
  int i;
  for(i = 0; i < numSets; i++){
    cache[i] = new CacheEntry[numWays];
    for(j = 0; j < numWays; j++){
      CacheEntry* c =  &cache[i][j];
      c->set = i;
      c->way = j;
      c->freq = 0;
      c->dirty = false;
      c->lru = 0;
    }
  }
  readHits = 0;
  readMisses = 0;
  writeHits = 0;
  writeMisses = 0;
  this->replacementPolicy = replacementPolicy;
  

}

Cache::read(int address){
  int set = getSet(address);
  int tag = getTag(address);
  int way;
  if((way = findTagInSet(tag)) != -1){
    readHits++;
    return;
  }else{
    readMisses++;
    get(address);
  }
}

Cache::write(address){
  int set = getSet(address);
  int tag = getTag(address);
  int way;
  
}
