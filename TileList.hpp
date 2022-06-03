// header guard
#ifndef TILELIST_HPP
#define TILELIST_HPP

#include "raylib.h"
#include "Tile.hpp"
#include <iostream>

using namespace std;

#define TILEOPTION_MAX 7


#define TILEIDX_GRASS 0
#define TILEIDX_SAND 1
#define TILEIDX_WATER 2
#define TILEIDX_OCEAN 3
#define TILEIDX_FOREST 4
#define TILEIDX_DEEPOCEAN 5
#define TILEIDX_PLAINS 6

class TileList{
    public:
    int tileOptionsCount;
    int totalAdded;
    Tile **tileOptions;

    //constructor
    TileList();

    //destructor
    ~TileList();

    Tile *getTileOption(int idx);

    void addTileOption(Tile *t);

    static int getTotalTiles();
};

#endif