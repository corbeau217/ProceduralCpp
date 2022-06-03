#include "raylib.h"
#include "CellTile.hpp"
#include "CellTileList.hpp"
#include <iostream>

using namespace std;




//constructor
CellTile::CellTile(const char *nameIn) {
    tileIdx = -1;
    tileName = nameIn;
    canBeNearTile = new bool[CellTileList::getTotalTiles()];
    for(int i = 0; i < CellTileList::getTotalTiles(); i++)
        canBeNearTile[i] = true;
    tileColor = WHITE;
}
CellTile::CellTile(const char *nameIn, Color colorIn) {
    tileIdx = -1;
    tileName = nameIn;
    canBeNearTile = new bool[CellTileList::getTotalTiles()];
    for(int i = 0; i < CellTileList::getTotalTiles(); i++)
        canBeNearTile[i] = true;
    tileColor = colorIn;
}
//destructor
CellTile::~CellTile(){
    delete canBeNearTile;
    delete tileName;
}

/**
 * @brief Get the index of this tile
 * 
 * @return int : returns -1 if no tile index was set
 */
int CellTile::getTileIdx(){
    return tileIdx;
}
/**
 * @brief Set the CellTile index
 * 
 * @param idx : index to set it to
 * 
 * has builder pattern
 */
CellTile *CellTile::setTileIdx(int idx){
    tileIdx = idx;
    return this;
}

bool CellTile::canBeNear(int idx){
    return canBeNearTile[idx];
}
/**
 * @brief check if can be near tile
 * 
 * @param t : tile to check
 * @return true : if adjacency allows this
 * @return false : otherwise
 * PRE: t was setup with valid tile index
 */
bool CellTile::canBeNear(CellTile *t){
    return canBeNear(t->getTileIdx());
}

CellTile *CellTile::setDisallowsAdjacency(int idx){
    canBeNearTile[idx] = false;
    return this;
}
/**
 * @brief Set cannot be near tile
 * 
 * @param t : tile cant be near
 * PRE: t was setup with valid tile index
 */
CellTile *CellTile::setDisallowsAdjacency(CellTile *t){
    return setDisallowsAdjacency(t->getTileIdx());
}

/**
 * @brief Set the color of this cell
 * 
 * @param c : color to set this tile to use
 * 
 * has builder pattern
 */
CellTile *CellTile::setColor(Color c){
    tileColor = c;
    return this;
}


/**
 * @brief Get the Color object
 * 
 * @return Color* : color of this tile
 */
Color *CellTile::getColor(){
    return &tileColor;
}


