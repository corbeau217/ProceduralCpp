#include "Seeder.hpp"
#include "Cell.hpp"
#include "Lattice.hpp"
#include "CellTileList.hpp"
#include <iostream>

using namespace std;



// constructor
Cell::Cell(int xIn, int yIn, int sIn, int colIn, int rowIn) {
        tileSet = false;
        xPos = xIn;
        yPos = yIn;
        width = sIn;
        height = sIn;
        col = colIn;
        row = rowIn;
        canBeCellTile = new bool[CellTileList::getTotalTiles()];
        for(int i = 0; i < CellTileList::getTotalTiles(); i++)
            canBeCellTile[i] = true;
        tile = nullptr;
    }
Cell::Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn) {
        tileSet = false;
        xPos = xIn;
        yPos = yIn;
        width = wIn;
        height = hIn;
        col = colIn;
        row = rowIn;
        canBeCellTile = new bool[CellTileList::getTotalTiles()];
        for(int i = 0; i < CellTileList::getTotalTiles(); i++)
            canBeCellTile[i] = true;
        tile = nullptr;
}
// destructor
Cell::~Cell(){
    delete tile;
    delete canBeCellTile;
}


int Cell::getCol(){
    return col;
}
int Cell::getRow(){
    return row;
}

/**
 * @brief checks if we've chosen a tile
 * 
 * @return true : no entropy
 * @return false : otherwise
 */
bool Cell::chosenCellTile(){
    return tileSet;
}

/**
 * @brief returns how many options this cell has
 * 
 * @return int : -1 if already set, otherwise returns the option count
 * 
 * TODO: check if this behaves correctly with empty tile reference, might need null tiles
 */
int Cell::getEntropy(){
    if(chosenCellTile())
        return -1;
    int counter = 0;
    for(int i = 0; i < CellTileList::getTotalTiles(); i++)
        if(canBeCellTile[i])
            ++counter;
    return counter;
}
bool Cell::hasEntropy(){
    return !chosenCellTile() && getEntropy()>0;
}

/**
 * @brief check if there's any options for this cell
 * 
 * @return true : there's at least one option this cell can choose
 * @return false : if no options / already collapsed this cell
 */
bool Cell::hasOptions(){
    return getEntropy()>0;
}


/**
 * @brief Set the CellTile object
 * 
 * @param t : tile object
 */
void Cell::setCellTile(CellTile *t){
    tile = t;
    for(int i = 0; i < CellTileList::getTotalTiles(); i++)
        canBeCellTile[i] = false;
    tileSet = true;
}

/**
 * @brief Get a reference to the tile this cell has
 * 
 * @return CellTile* : returns nullptr if still has entropy
 */
CellTile *Cell::getCellTile(){
    if(chosenCellTile())
        return tile;
    return nullptr;
}


/**
 * @brief tell this cell it's nearby a tile
 * 
 * @param t : the tile reference it's nearby
 * @return true : if there was a change to this cell's options
 * @return false : otherwise
 */
bool Cell::propagateNearbyCellTile(CellTile *t){
    bool didWeModify = false;
    // loop through all tile options
    for(int i = 0; i < CellTileList::getTotalTiles(); i++){
        if(canBeCellTile[i]){
            //store if we can be near
            canBeCellTile[i] = Lattice::getCellTileOption(i)->canBeNear(t);
            if(!canBeCellTile[i])
                // suddenly we cant, mark that there was an update
                didWeModify = true;
        }
    }
    return didWeModify;
}

/**
 * @brief : choose random option available out of the tile options
 * 
 * @return true : if there was any change that would need propagation
 * @return false : no change due to error or due to no need
 */
bool Cell::collapse(){
    // get how many options we can be
    int optionCount = getEntropy();
    if(optionCount<1) // no options return false
        return false;
    // otherwise we choose an option randomly
    int randomExistingOption = Seeder::getRandom(optionCount);
    // loop through our options to find the one we chose
    for(int i = 0, k = 0; i < CellTileList::getTotalTiles(); i++){
        // check is valid option
        if(canBeCellTile[i]){
            // check random number
            if(k==randomExistingOption){
                //we found our option, collapse to this one
                setCellTile(Lattice::getCellTileOption(i));
                return true;
            }
            ++k;
        }
    }
    return false;
}

/**
 * @brief handles drawing the frame of the cell
 * 
 */
void Cell::paint(){
    Color tileColor;
    // try get tile color
    if(chosenCellTile())
        tileColor = *(tile->getColor());
    else
        tileColor = WHITE;
    // draw fill
    DrawRectangle(xPos,yPos,width,height,tileColor);
    // draw outline
    DrawRectangleLines(xPos,yPos,width,height,(Color){20,20,20,255});
}







