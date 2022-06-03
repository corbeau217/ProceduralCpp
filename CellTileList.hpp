// header guard
#ifndef CELLTILELIST_HPP
#define CELLTILELIST_HPP

#include "raylib.h"
#include "CellTile.hpp"
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

/**
 * @brief this holds the options for our tiles we can use on cells
 * 
 */
class CellTileList{
    public:
    int tileOptionsCount;
    int totalAdded;
    CellTile **tileOptions;

    //constructor
    CellTileList();

    //destructor
    ~CellTileList();

    CellTile *getTileOption(int idx);

    void addTileOption(CellTile *t);

    static int getTotalTiles();
};

#endif