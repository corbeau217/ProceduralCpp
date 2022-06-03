#include "raylib.h"
#include "Tile.hpp"
#include "TileList.hpp"
#include <iostream>

using namespace std;




//constructor
Tile::Tile(const char *nameIn) {
    tileIdx = -1;
    tileName = nameIn;
    canBeNearTile = new bool[TileList::getTotalTiles()];
    for(int i = 0; i < TileList::getTotalTiles(); i++)
        canBeNearTile[i] = true;
    tileColor = WHITE;
}
Tile::Tile(const char *nameIn, Color colorIn) {
    tileIdx = -1;
    tileName = nameIn;
    canBeNearTile = new bool[TileList::getTotalTiles()];
    for(int i = 0; i < TileList::getTotalTiles(); i++)
        canBeNearTile[i] = true;
    tileColor = colorIn;
}
//destructor
Tile::~Tile(){
    delete canBeNearTile;
    delete tileName;
}

/**
 * @brief Get the index of this tile
 * 
 * @return int : returns -1 if no tile index was set
 */
int Tile::getTileIdx(){
    return tileIdx;
}
/**
 * @brief Set the Tile index
 * 
 * @param idx : index to set it to
 * 
 * has builder pattern
 */
Tile *Tile::setTileIdx(int idx){
    tileIdx = idx;
    return this;
}

bool Tile::canBeNear(int idx){
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
bool Tile::canBeNear(Tile *t){
    return canBeNear(t->getTileIdx());
}

Tile *Tile::setDisallowsAdjacency(int idx){
    canBeNearTile[idx] = false;
    return this;
}
/**
 * @brief Set cannot be near tile
 * 
 * @param t : tile cant be near
 * PRE: t was setup with valid tile index
 */
Tile *Tile::setDisallowsAdjacency(Tile *t){
    return setDisallowsAdjacency(t->getTileIdx());
}

/**
 * @brief Set the color of this cell
 * 
 * @param c : color to set this tile to use
 * 
 * has builder pattern
 */
Tile *Tile::setColor(Color c){
    tileColor = c;
    return this;
}


/**
 * @brief Get the Color object
 * 
 * @return Color* : color of this tile
 */
Color *Tile::getColor(){
    return &tileColor;
}


