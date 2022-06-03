// header guard
#ifndef CELL_HPP
#define CELL_HPP

#include "CellTile.hpp"
#include <iostream>

using namespace std;

#define TILEOPTIONCOUNT 7



/**
 * @brief this is the cell object that goes into lattice
 * 
 */
class Cell {
    public:
    // drawing variables
    int xPos;
    int yPos;
    int width;
    int height;
    // lattice variables
    int col;
    int row;
    // these are for tile option
    CellTile* tile;
    // keeps track of whether we've set this to have a tile yet
    bool tileSet;
    // keep track of what tiles we can be
    bool* canBeCellTile;

    // constructor
    Cell(int xIn, int yIn, int sIn, int colIn, int rowIn);
    Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn);
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
    bool chosenCellTile();

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
     * @brief Set the CellTile object
     * 
     * @param t : tile object
     */
    void setCellTile(CellTile *t);

    /**
     * @brief Get a reference to the tile this cell has
     * 
     * @return CellTile* : returns nullptr if still has entropy
     */
    CellTile *getCellTile();


    /**
     * @brief tell this cell it's nearby a tile
     * 
     * @param t : the tile reference it's nearby
     * @return true : if there was a change to this cell's options
     * @return false : otherwise
     */
    bool propagateNearbyCellTile(CellTile *t);

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
