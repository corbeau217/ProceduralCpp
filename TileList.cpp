#include "TileList.hpp"
#include <iostream>

using namespace std;

#define TILEOPTIONS 7


#define TILEIDX_GRASS 0
#define TILEIDX_SAND 1
#define TILEIDX_WATER 2
#define TILEIDX_OCEAN 3
#define TILEIDX_FOREST 4
#define TILEIDX_DEEPOCEAN 5
#define TILEIDX_PLAINS 6


//constructor
TileList::TileList(int total){
    tileOptionsCount = total;
    totalAdded = 0;
    tileOptions = new Tile*[tileOptionsCount];
    for(int i = 0; i < tileOptionsCount; i++)
        tileOptions[i] = nullptr;
}
//destructor
TileList::~TileList(){
    for(int i = 0; i < tileOptionsCount; i++)
        delete tileOptions[i];
    delete tileOptions;
}




Tile *TileList::getTileOption(int idx){
    return tileOptions[idx];
}

void TileList::addTileOption(Tile *t){
    if(totalAdded<tileOptionsCount){
        tileOptions[totalAdded] = t;
        ++totalAdded;
    }
}

int TileList::getTotalTiles(){
    return totalAdded;
}
