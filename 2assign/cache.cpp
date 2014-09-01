#include"cache.h"

Cache::Cache(int id, int size, int associativity, int blockSize, int replacementPolicy){
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
  this->id = id;

}

void Cache::read(int address){
  int set = getSet(address);
  int tag = getTag(address);
  int way;
  if((way = findTagInSet(tag)) != -1){ // address present in cache
    readHits++;
    cache[set][way].lru = 1;
    cache[set][way].freq++;
  }else{ // address not in cache/set
    readMisses++;
    get(address); // get data from higher level cache
    way = getVictim(set); // get victim from the set
    if(cache[set][way].dirty){ // if dirty, 
      put(generatePseudoAddress(set, tag)); // evict to higher level cache
    }
    cache[set][way].tag = tag; // install data/tag in cache line
    cache[set][way].lru = 1;
    cache[set][way].dirty = false;
    cache[set][way].freq = 1;
  }
}

void Cache::write(int address){
  int set = getSet(address);
  int tag = getTag(address);
  int way;
  if((way = findTagInSet(tag)) != -1){ // address present in cache
    writeHits++;
    cache[set][way].dirty = true;
    cache[set][way].lru = 1;
    cache[set][way].freq++;
  }else{ // address not in cache/set
    writeMisses++;
    get(address); // get data from higher level cache
    way = getVictim(set); // get victim from the set
    if(cache[set][way].dirty){ // if dirty, 
      put(generatePseudoAddress(set, tag)); // evict to higher level cache
    }
    cache[set][way].tag = tag; // install data/tag in cache line
    cache[set][way].lru = 1;
    cache[set][way].dirty = true; // because we're writing to it
    cache[set][way].freq = 1;
  }
}

void Cache::get(int address){
  if(id+1 != wrapper->ramID){
    wrapper->cacheArray[id+1].read(address);
  }
}

void Cache::put(int address){
  if(id+1 != wrapper->ramID){
    wrapper->cacheArray[id+1].write(address);
  }
}
