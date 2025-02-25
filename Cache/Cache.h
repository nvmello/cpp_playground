//
// Created by parallels on 2/24/25.
//

#ifndef CACHE_H
#define CACHE_H
#include <bits/stdc++.h>
#include "LRU/LRU_Cache.h"
using namespace std;

class Cache {

  private:
    size_t totalSizeBytes;    //block size * associativity
    size_t blockSizeBytes;    //six of each block
    size_t associativity;     //number of ways
    size_t numSets;            //numSets = totalSizeBytes / (blockSizeBytes * associativity)
    vector<LRU_Cache*> lruCaches;
    
    public:
      Cache(size_t cacheSize, size_t blockSize, size_t ways){
        if (cacheSize > 256 * 1024){
          throw invalid_argument("Cache size exceeds maximum of 256 KiB");
        }
        if  (blockSize > 64){
          throw invalid_argument("Block size exceeds maximum of 64 MB");
        }
        if  (ways > 8){
          throw invalid_argument("Associativity exceeds maximum of 8-Way");
        }
        totalSizeBytes = cacheSize;
        blockSizeBytes = blockSize;
        associativity = ways;
        numSets = totalSizeBytes / (blockSizeBytes * associativity);

        for (size_t i = 0; i < numSets; i++){
          lruCaches.push_back(new LRU_Cache(associativity));
        }
       }

    bool access(size_t address) {
        // set index
        size_t setIndex = (address / blockSizeBytes) % numSets;
        size_t tag = (address / blockSizeBytes) / numSets;

        // Check if the tag is in the cache
        bool hit = lruCaches[setIndex]->get(tag);

        // If miss update the cache
        if (!hit) {
          lruCaches[setIndex]->put(tag);
        }

        return hit;
      }
};

#endif //CACHE_H
