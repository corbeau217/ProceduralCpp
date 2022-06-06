// header guard
#ifndef CELL_HPP
#define CELL_HPP

#include "Util.hpp"
#include "Tile.hpp"
#include <iostream>

using namespace std;

#define TILEOPTIONCOUNT 7



/**
 * @brief this is the cell that goes into lattice
 * 
 */
class Cell {
    public:
    rect *guiPlacement;
    int2D *loc;

    // these are for tile option
    Tile* tile;
    // keeps track of whether we've set this to have a tile yet
    bool tileSet;
    // keep track of what tiles we can be
    bool* canBeTile;

    // constructor
    Cell(rect *inPlacement, int2D *locIn);
    // destructor
    ~Cell();


    int getCol();
    int getRow();

    /**
     * @brief checks if we've chosen a tile
     * 
     * @return true : no entropy
     * @return false : otherwise
     */
    bool chosenTile();

    /**
     * @brief returns how many options this cell has
     * 
     * @return int : -1 if already set, otherwise returns the option count
     * 
     * TODO: check if this behaves correctly with empty tile reference, might need null tiles
     */
    int getEntropy();
    bool hasEntropy();

    /**
     * @brief check if there's any options for this cell
     * 
     * @return true : there's at least one option this cell can choose
     * @return false : if no options / already collapsed this cell
     */
    bool hasOptions();


    /**
     * @brief Set the Tile object
     * 
     * @param t : tile object
     */
    void setTile(Tile *t);

    /**
     * @brief Get a reference to the tile this cell has
     * 
     * @return Tile* : returns nullptr if still has entropy
     */
    Tile *getTile();


    /**
     * @brief tell this cell it's nearby a tile
     * 
     * @param t : the tile reference it's nearby
     * @return true : if there was a change to this cell's options
     * @return false : otherwise
     */
    bool propagateNearbyTile(Tile *t);

    /**
     * @brief : choose random option available out of the tile options
     * 
     * @return true : if there was any change that would need propagation
     * @return false : no change due to error or due to no need
     */
    bool collapse();

    /**
     * @brief handles drawing the frame of the cell
     * 
     */
    void paint();




};

#endif
