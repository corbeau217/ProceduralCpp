// header guard
#ifndef LATTICE_HPP
#define LATTICE_HPP

#include "Cell.hpp"
#include "Seeder.hpp"
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
    Lattice(int2D *drawPos, int2D *cellCountIn, int cellSizeIn);

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
     * @brief returns the current iterator int2D pointer
     * 
     */
    int2D *getIterPos();


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


};

#endif