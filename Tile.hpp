// header guard
#ifndef TILE_HPP
#define TILE_HPP

#include "raylib.h"
#include <iostream>

using namespace std;




/**
 * @brief this is the tiles that we can use
 * 
 * 
 */
class Tile{
    public:
    int tileIdx;
    bool *canBeNearTile;
    const char *tileName;
    Color tileColor;


    //constructor
    Tile(const char *nameIn);
    Tile(const char *nameIn, Color colorIn);

    //destructor
    ~Tile();

    /**
     * @brief Get the index of this tile
     * 
     * @return int : returns -1 if no tile index was set
     */
    int getTileIdx();

    /**
     * @brief Set the Tile index
     * 
     * @param idx : index to set it to
     * 
     * has builder pattern
     */
    Tile *setTileIdx(int idx);

    bool canBeNear(int idx);

    /**
     * @brief check if can be near tile
     * 
     * @param t : tile to check
     * @return true : if adjacency allows this
     * @return false : otherwise
     * PRE: t was setup with valid tile index
     */
    bool canBeNear(Tile *t);

    Tile *setDisallowsAdjacency(int idx);

    /**
     * @brief Set cannot be near tile
     * 
     * @param t : tile cant be near
     * PRE: t was setup with valid tile index
     */
    Tile *setDisallowsAdjacency(Tile *t);

    /**
     * @brief Set the color of this cell
     * 
     * @param c : color to set this tile to use
     * 
     * has builder pattern
     */
    Tile *setColor(Color c);


    /**
     * @brief Get the Color object
     * 
     * @return Color* : color of this tile
     */
    Color *getColor();


};


#endif