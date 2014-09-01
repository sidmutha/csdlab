#include"cache.h"
#include <cstdlib>
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

Cache::getVictim(int set){
	int i,j,way,min;
	switch(replacementPolicy){
		case 0:
		  //Finding least recently used address
			for(i = 0; i < numWays; i++)
				if(cache[set][i].lru == 0){
            way = i;
						break;
			 }
		  break;
		case 1:
			//Finding minimum frequency address
			min = cache[set][0];
			way =0;
			for(i=1;i<numWays;i++)
					if(min < cache[set][i].freq){
						min = cache[set][i].freq;
						way = i;
					}
		
			break;
 		case 2:
			way = rand() % numWays;
			break;

	return way;
}
		

