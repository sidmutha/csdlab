#include"cache.h"
#include"wrapper.h"
#include<cstdlib>
#include<time.h>
#include<math.h>

Cache::Cache(int id, Wrapper *w, int size, int associativity, int blockSize, int replacementPolicy){
  numSets = size * 1024 / (associativity * blockSize);
  numWays = associativity;
  cache = new CacheEntry*[numSets];
  srand(time(NULL));
  int i, j;
  for(i = 0; i < numSets; i++){
    cache[i] = new CacheEntry[numWays];
    for(j = 0; j < numWays; j++){
      CacheEntry* c =  &cache[i][j];
      c->set = i;
      c->way = j;
      c->freq = 0;
      c->dirty = false;
      c->lru = 0;
      c->state = 0;
    }
  }
  readHits = 0;
  readMisses = 0;
  writeHits = 0;
  writeMisses = 0;
  this->replacementPolicy = replacementPolicy;
  this->id = id;
  this->wrapper = w;
  this->offsetBits = log2(blockSize);
  this->setBits = log2(numSets);
  this->tagBits = 64 - offsetBits - setBits;
}


void Cache::read(uint64_t address){
  int set = getSet(address);
  uint64_t tag = getTag(address);
  int way;
  if((way = findTagInSet(tag, set)) != -1){ // address present in cache
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
    delete(address);
    cache[set][way].tag = tag; // install data/tag in cache line
    cache[set][way].lru = 1;
    cache[set][way].dirty = false;
    cache[set][way].freq = 1;
    cache[set][way].state =1;	
  }
}

void Cache::write(uint64_t address){
  int set = getSet(address);
  uint64_t tag = getTag(address);
  int way;
  if((way = findTagInSet(tag, set)) != -1){ // address present in cache
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
    delete(address);
    cache[set][way].tag = tag; // install data/tag in cache line
    cache[set][way].lru = 1;
    cache[set][way].dirty = true; // because we're writing to it
    cache[set][way].freq = 1;
    cache[set][way].state = 1 ;
  }
}

int Cache::getSet(uint64_t address){
  return ((address << tagBits) >> (tagBits + offsetBits));
}

uint64_t Cache::getTag(uint64_t address){
  return address >> (64 - tagBits);
}

uint64_t Cache::generatePseudoAddress(int set, uint64_t tag){
  //return 0;
}

int Cache::findTagInSet(uint64_t tag, int set){
  int i;
  for(i = 0; i < numWays; i++){
    if(cache[set][i].tag == tag && cache[set][way].state == 1){
      return i;
    }
  }
}

void Cache::get(uint64_t address){
  if(id+1 != wrapper->ramID){
    wrapper->cacheArray[id+1].read(address);
  }
}

void Cache::put(uint64_t address){
  if(id+1 != wrapper->ramID){
    wrapper->cacheArray[id+1].write(address);
  }
}

void Cache::delete(uint64_t address){
   int set,way;
   uint64_t tag;
   set = getSet(address);
   tag = getTag(address);	
   way = findTagInSet(tag, set);
   cache[set][way].state =0;
  if(id == 0)
		return;

	wrapper->cacheArray[id-1].delete(address); 		   		 

}
int Cache::getVictim(int set){
  int i, j, way, min;
  switch(replacementPolicy){
  case 0:
    // Finding least recently used address
    for(i = 0; i < numWays; i++)
      if(cache[set][i].lru == 0){
	way = i;
	break;
      }
    break;
  case 1:
    // Finding minimum frequency address
    min = cache[set][0].freq;
    way = 0;
    for(i = 1; i < numWays; i++)
      if(min < cache[set][i].freq){
	min = cache[set][i].freq;
	way = i;
      }
    break;
  case 2://Random eviction policy
    way = rand() % numWays;
    break;    
  }
  return way;  
}		

Cache::Cache(){
  
}
