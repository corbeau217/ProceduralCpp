
#include "Cell.hpp"
#include "Seeder.hpp"
#include "Lattice.hpp"
#include <iostream>

using namespace std;




/**
 * @brief this is the cell that goes into lattice
 * 
 */

// constructor
Cell::Cell(rect *inPlacement, int2D *locIn){
    guiPlacement = inPlacement;
    loc = locIn;

}
// destructor
Cell::~Cell(){
    delete guiPlacement;
    delete loc;
}


int Cell::getCol(){
    return loc->x;
}
int Cell::getRow(){
    return loc->y;
}

bool Cell::colorSet(){
    //TODO
    return false;
}

/**
 * @brief handles drawing the frame of the cell
 * 
 */
void Cell::paint(){
    Color tileColor;
    // try get tile color
    if(colorSet())
        tileColor = *cellColor;
    else
        tileColor = WHITE;
    // draw fill
    DrawRectangle(
        guiPlacement->x,
        guiPlacement->y,
        guiPlacement->width,
        guiPlacement->height,
        tileColor);
    // draw outline
    DrawRectangleLines(
        guiPlacement->x,
        guiPlacement->y,
        guiPlacement->width,
        guiPlacement->height,
        (Color){20,20,20,255});
}







