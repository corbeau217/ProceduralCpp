#include "Lattice.hpp"
#include "Lib.hpp"
#include <iostream>

using namespace std;

#define SHOWCELLPROGRESS false

/**
 * @brief try with using array of indexes for dealing with things or using an array of Cell pointers
 * 
 * TODO: look into c++ form of functional interfaces for
 *       set this up with a "doToEach" function that takes 
 *      a function to apply to every element
 */

// constructor
Lattice::Lattice(int2D *drawPos, int2D *cellCountIn, int cellSizeIn) {
    cout << "--> [setting up]: Lattice object" << endl;
    // draw position member
    pos = new int2D{drawPos->x, drawPos->y};
    // cell col/row counts
    cellCount = cellCountIn;
    // total cell count
    totalCells = (cellCount->x) * (cellCount->y);
    // initialise the total filled var
    filledCells = 0;
    // cell width/height var
    cellSize = cellSizeIn;
    // iter handle
    iterPos = new int2D{0, 0};

    // have a colCount length array of Cell** 
    cout << "--> [Generating]: cells pointer array" << endl;
    cells = new Cell**[cellCount->x];
    for(int x = 0; x < cellCount->x; x++){
        // each Cell* is rowCount of Cell*
        cells[x] = new Cell*[cellCount->y];
        for(int y = 0; y < cellCount->y; y++){
            // make the cell
            cells[x][y] = new Cell(
                // cell ui placement
                new rect{
                    (pos->x) + x*cellSize,
                    (pos->y) + y*cellSize,
                    cellSize,
                    cellSize
                },
                // cell location
                new int2D{x,y}
            );
        }
    }
    builtGrid = false;
    
    //TODO
}

// destructor
Lattice::~Lattice(){
    for(int x = 0; x < cellCount->x; x++){
        for(int y = 0; y < cellCount->y; y++){
                delete cells[x][y];
        }
        delete cells[x];
    }
    delete cells;
    // todo
}


/**
 * @brief used for the iterator pattern on our lattice
 * 
 * @return true : if at last position
 * @return false : otherwise
 */
bool Lattice::iterDone(){
    return iterPos->y >= cellCount->y;
}
/**
 * @brief move to next location
 * 
 */
void Lattice::iterNext(){
    if(iterPos->x == cellCount->x-1){
        iterPos->x = 0;
        iterPos->y += 1;
    }
    else
        iterPos->x += 1;
}
/**
 * @brief reset our iterPos to first location
 * 
 */
void Lattice::iterBegin(){
    iterPos->x = 0;
    iterPos->y = 0;
}
/**
 * @brief returns current iterator location
 * 
 */
Cell *Lattice::iterCurrent(){
    return  get(iterPos);
}
int2D *Lattice::getIterPos(){
    return iterPos;
}


/**
 * @brief checks if there is a valid location with col and row idx
 * 
 * @param col col idx
 * @param row row idx
 * @return true if we can access that location
 * @return false otherwise
 */
bool Lattice::isValidLocation(int col, int row){
    return (col>-1&&row>-1)&&(col<cellCount->x&&row<cellCount->y);
}

/**
 * @brief : get the cell at col row
 * 
 * @param col : col idx to get from
 * @param row : row idx to get from
 * @return Cell *: pointer to cell
 */
Cell *Lattice::get(int col, int row){
    if(isValidLocation(col,row))
        return cells[col][row];
    return nullptr;
}
Cell *Lattice::get(int2D *locIn){
    return get(locIn->x, locIn->y);
}



/**
 * @brief loops until all cells collapsed
 *          handing off to `collapseNext()`
 *          for each iteration
 */
void Lattice::buildLattice(){
    cout << "--> [Running]: Lattice::buildLattice()" << endl;

    // setup RandomSeeder
    cout << "--> [Hand off]: going to RandomSeeder::setup() before build" << endl;
    latticeSeeder = new Seeder(Lib::getSeed());

    //TODO


    // tell everyone we're done building
    builtGrid = true;
    cout << "--> Done building lattice" << endl;
}

/**
 * @brief paints a frame of lattice
 * 
 */
void Lattice::paint(){
    // build grid if needed
    if(!builtGrid)
        buildLattice();
    // paint the cells
    for(iterBegin(); !iterDone(); iterNext())
            iterCurrent()->paint();
}
