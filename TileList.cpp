#include "TileList.hpp"
#include <iostream>

using namespace std;


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
    return TILEOPTIONS;
}
