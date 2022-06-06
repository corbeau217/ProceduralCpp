// header guard
#ifndef LATTICE_HPP
#define LATTICE_HPP

#include "Cell.hpp"
#include "Seeder.hpp"
#include "TileList.hpp"
#include "Util.hpp"
#include <iostream>

using namespace std;



#define ADJACENT_LIST_SIZE 8

/**
 * @brief try with using array of indexes for dealing with things or using an array of Cell pointers
 * 
 */
class Lattice{
    public:
    static TileList *tiles;
    // our cell grid
    int2D *pos;
    int2D *cellCount;
    Cell*** cells;
    // other stuff
    int cellSize;
    bool builtGrid;
    int totalCells;
    int filledCells;
    // iter variable
    int2D *iterPos;

    // constructor
    Lattice(int2D *drawPos, int colCountIn, int rowCountIn, int cellSizeIn);

    // destructor
    ~Lattice();

    /**
     * @brief used for the iterator pattern on our lattice
     * 
     * @return true : if at last position
     * @return false : otherwise
     */
    bool iterDone();
    /**
     * @brief move to next location
     * 
     */
    void iterNext();
    /**
     * @brief reset our iterPos to first location
     * 
     */
    void iterBegin();
    /**
     * @brief returns current iterator location
     * 
     */
    Cell *iterCurrent();


    /**
     * @brief checks if there is a valid location with col and row idx
     * 
     * @param col col idx
     * @param row row idx
     * @return true if we can access that location
     * @return false otherwise
     */
    bool isValidLocation(int col, int row);

    /**
     * @brief : get the cell at col row
     * 
     * @param col : col idx to get from
     * @param row : row idx to get from
     * @return Cell *: pointer to cell
     */
    Cell *get(int col, int row);
    Cell *get(int2D *locIn);
    
    /**
     * @brief returns if there's any entropy in the lattice
     * 
     * @return true : if any cell has entropy
     * @return false : otherwise
     */
    bool hasEntropy();

    /**
     * @brief Get lowest entropy of any cell in the lattice
     * 
     * @return int : lowest entropy in choices
     */
    int getLowestEntropy();

    /**
     * @brief Get the count of cells with that entropy
     * 
     * @param entropyVal : value to count
     * @return int : the count of cells with that entropy
     */
    int getHasEntropyCount(int entropyVal);

    /**
     * @brief Get the count of how many cells have the lowest entropy
     * 
     * @return int : number of cells with lowest entropy
     */
    int getLowestEntropyCount();
    /**
     * @brief Get the Lowest Entropy List object
     * 
     * length of this array can be found by using getLowestEntropyCount()
     */
    Cell **getLowestEntropyList();

    /**
     * @brief Get the cell with the lowest entropy in a given list
     * 
     * @return Cell *: pointer of the cell
     */
    Cell *getLowestEntropyCell();

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-7 with 0 being up
     * @return int : the change in x index
     */
    int dirX(int dir);

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-7 with 0 being up
     * @return int : the change in y index
     */
    int dirY(int dir);

    /**
     * @brief Get a list of the adjacent cells
     * 
     * @param xIdx : the index of x to get from
     * @param yIdx : the index of y to get from
     * length is always 8
     */
    Cell **getAdjacencyArray(int xIdx, int yIdx);
    
    /**
     * @brief collapse at location, return if we need to propagate
     * 
     * @param xIdx : the index of x to collapse
     * @param yIdx : the index of y to collapse
     * @return true : changed the cell and need to propagate
     *          TODO: improvement can be made by testing if adjacent cells are affected by change
     * @return false : no change/error
     * 
     * PRE: get(xIdx,yIdx) cell is valid and has entropy
     * POST: we've run a collapse function on the cell
     */
    bool collapse(int xIdx, int yIdx);
    
    /**
     * @brief propagate changes to a cell
     * 
     * @param xIdx : the index of x to propagate
     * @param yIdx : the index of y to propagate
     * @return true : if there was a change in entropy of any cell
     * @return false : if no change to entropy of any cell
     * 
     * PRE: propagation is required because collapse changed something
     * 
     */
    bool propagate(int xIdx, int yIdx);

    /**
     * @brief handles collapsing the next cell
     * 
     * PRE: somewhere in the lattice we have entropy
     * POST: handled a collapse and any needed propagation for the collapse
     * 
     */
    void collapseNext();
    
    /**
     * @brief loops until all cells collapsed
     *          handing off to `collapseNext()`
     *          for each iteration
     */
    void buildLattice();

    /**
     * @brief paints a frame of lattice
     * 
     */
    void paint();


    static Tile *getTileOption(int idx);

};

#endif