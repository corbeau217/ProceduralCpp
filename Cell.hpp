// header guard
#ifndef CELL_HPP
#define CELL_HPP

#include "Util.hpp"
#include "raylib.h"
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
    Color *cellColor;
    bool colorSetForCell;


    // constructor
    Cell(rect *inPlacement, int2D *locIn);
    // destructor
    ~Cell();


    int getCol();
    int getRow();

    bool colorSet();

    /**
     * @brief handles drawing the frame of the cell
     * 
     */
    void paint();




};

#endif
