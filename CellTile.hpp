// header guard
#ifndef CELLTILE_HPP
#define CELLTILE_HPP

#include "raylib.h"
#include <iostream>

using namespace std;




/**
 * @brief this is the tile instances we can use
 * 
 * 
 */
class CellTile{
    public:
    int tileIdx;
    bool *canBeNearTile;
    const char *tileName;
    Color tileColor;


    //constructor
    CellTile(const char *nameIn);
    CellTile(const char *nameIn, Color colorIn);

    //destructor
    ~CellTile();

    /**
     * @brief Get the index of this tile
     * 
     * @return int : returns -1 if no tile index was set
     */
    int getTileIdx();

    /**
     * @brief Set the CellTile index
     * 
     * @param idx : index to set it to
     * 
     * has builder pattern
     */
    CellTile *setTileIdx(int idx);

    bool canBeNear(int idx);

    /**
     * @brief check if can be near tile
     * 
     * @param t : tile to check
     * @return true : if adjacency allows this
     * @return false : otherwise
     * PRE: t was setup with valid tile index
     */
    bool canBeNear(CellTile *t);

    CellTile *setDisallowsAdjacency(int idx);

    /**
     * @brief Set cannot be near tile
     * 
     * @param t : tile cant be near
     * PRE: t was setup with valid tile index
     */
    CellTile *setDisallowsAdjacency(CellTile *t);

    /**
     * @brief Set the color of this cell
     * 
     * @param c : color to set this tile to use
     * 
     * has builder pattern
     */
    CellTile *setColor(Color c);


    /**
     * @brief Get the Color object
     * 
     * @return Color* : color of this tile
     */
    Color *getColor();


};


#endif