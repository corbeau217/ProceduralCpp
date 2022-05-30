#include "Cell.cpp"
#include <iostream>

using namespace std;



class Randoming{
    public:
    /**
     * @brief Get random number within bounding
     * 
     * @param bounding : return is less than this value
     * @return int : value between 0 and bounding
     */
    static int getRandom(int bounding){
        //TODO
        return 0;
    }
};

#define TILEOPTIONS 5
#define ADJACENT_LIST_SIZE 8

/**
 * @brief try with using array of indexes for dealing with things or using an array of Cell pointers
 * 
 */
class Lattice{
    public:
    // constructor
    Lattice(int xLoc, int yLoc, int colCountIn, int rowCountIn, int cellSizeIn) {

        xPos = xLoc;
        yPos = yLoc;
        colCount = colCountIn;
        rowCount = rowCountIn;
        cellSize = cellSizeIn;
        // have a colCount length array of Cell** 
        cells = new Cell**[colCount];
        for(int idx = 0; idx < colCount; idx++)
            // each Cell* is rowCount of Cell*
            cells[idx] = new Cell*[rowCount];
        builtGrid = false;
    }

    // destructor
    ~Lattice(){
        for(int x = 0; x < colCount; x++){
            for(int y = 0; y < rowCount; y++){
                 delete cells[x][y];
            }
            delete cells[x];
        }
        delete cells;
    }

    /**
     * @brief checks if there is a valid location with col and row idx
     * 
     * @param col col idx
     * @param row row idx
     * @return true if we can access that location
     * @return false otherwise
     */
    bool isValidLocation(int col, int row){
        return (col>-1&&row>-1)&&(col<colCount&&row<rowCount);
    }

    /**
     * @brief : get the cell at col row
     * 
     * @param col : col idx to get from
     * @param row : row idx to get from
     * @return Cell *: pointer to cell
     */
    Cell *get(int col, int row){
        if(isValidLocation(col,row))
            return cells[col][row];
        return nullptr;
    }
    
    /**
     * @brief returns if there's any superposition cells
     * 
     * @return true : if any cell has entropy
     * @return false : otherwise
     */
    bool hasEntropy(){
        // loop through and check entropy
        for(int x = 0; x < colCount; x++){
            for(int y = 0; y < rowCount; y++){
                bool currCellEntropy = get(x,y)->hasEntropy();
                // return true if cell has entropy
                if(currCellEntropy) return true;
            }
        }
        return false;
    }

    /**
     * @brief Get lowest entropy of any cell in the lattice
     * 
     * @return int : lowest entropy in choices
     */
    int getLowestEntropy(){
        // start with highest possible
        int lowestEntropy = TILEOPTIONS;
        // loop through and check for something lower
        for(int x = 0; x < colCount; x++){
            for(int y = 0; y < rowCount; y++){
                int currCellEntropy = get(x,y)->getEntropy();
                if(currCellEntropy<lowestEntropy)
                    lowestEntropy = currCellEntropy;
            }
        }
        return lowestEntropy;
    }

    /**
     * @brief Get the count of cells with that entropy
     * 
     * @param entropyVal : value to count
     * @return int : the count of cells with that entropy
     */
    int getHasEntropyCount(int entropyVal){
        // counter for total matching
        int totalLowest = 0;
        // loop through and check
        for(int x = 0; x < colCount; x++){
            for(int y = 0; y < rowCount; y++){
                int currCellEntropy = get(x,y)->getEntropy();
                if(currCellEntropy<entropyVal)
                    ++totalLowest;
            }
        }
        return totalLowest;
    }

    /**
     * @brief Get the count of how many cells have the lowest entropy
     * 
     * @return int : number of cells with lowest entropy
     */
    int getLowestEntropyCount(){
        // get lowest entropy
        int lowestEntropy = getLowestEntropy();
        return getHasEntropyCount(lowestEntropy);
    }

    /**
     * @brief Get the Lowest Entropy List object
     * 
     * length of this array can be found by using getLowestEntropyCount()
     */
    Cell **getLowestEntropyList(){
        // what the lowest entropy is
        int lowestEntropy = getLowestEntropy();
        // to know how many we need to mess with
        int lowestEntropyCount = getHasEntropyCount(lowestEntropy);
        // TODO : needs to move into own class
        Cell **outList = new Cell*[lowestEntropyCount];
        // keep track of our current place in the array
        int currCount = 0;
        // loop through to find matching cells
        for(int x = 0; x < colCount; x++){
            for(int y = 0; y < rowCount; y++){
                // check if it has lowest entropy
                if(get(x,y)->getEntropy()==lowestEntropy){
                    // add to our array if it does
                    outList[currCount] = get(x,y);
                    //update our tracker
                    ++currCount;
                }
            }
        }
        return outList;
    }

    /**
     * @brief Get the cell with the lowest entropy in a given list
     * 
     * @return Cell *: pointer of the cell
     */
    Cell *getLowestEntropyCell(){
        int lowestEntropyCount = getLowestEntropyCount();
        Cell **lowestEntropyList = getLowestEntropyList();
        // choose a random option and return
        return lowestEntropyList[Randoming::getRandom(lowestEntropyCount)];
    }

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-7 with 0 being up
     * @return int : the change in x index
     */
    int dirX(int dir){
        switch (dir) {
        case 0:
        case 4:
        default:
            return 0;
        case 1:
        case 2:
        case 3:
            return 1;
        case 5:
        case 6:
        case 7:
            return -1;
        }
    }

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-7 with 0 being up
     * @return int : the change in y index
     */
    int dirY(int dir){
        switch(dir){
            case 0:
            case 1:
            case 7:
                return 1;
            case 2:
            case 6:
            default:
                return 0;
            case 3:
            case 4:
            case 5:
                return -1;
        }
    }

    /**
     * @brief Get a list of the adjacent cells
     * 
     * @param xIdx : the index of x to get from
     * @param yIdx : the index of y to get from
     * length is always 8
     */
    Cell **getAdjacencyArray(int xIdx, int yIdx){
        // initialise array of cells
        Cell **adjacencyArray = new Cell*[8];
        // loop through the directions
        for(int i = 0; i < 8; i++){
            // add the direction modifier and position
            int x = dirX(i) + xIdx;
            int y = dirY(i) + yIdx;
            // get the cell and dump into array
            *adjacencyArray = get(x,y);
        }
        return adjacencyArray;
    }
    
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
    bool collapse(int xIdx, int yIdx){
        // run collapse on specified cell
        return get(xIdx,yIdx)->collapse();
    }
    
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
     * TODO: after changing adjacent cells, we should check the cells adjacent to
     *      those for if they no longer have adjacent options required for some
     *      of their options (like if sand isnt possible at the adjacent cells, take out
     *      water as an option for cell in question)
     */
    bool propagate(int xIdx, int yIdx){
        // reference to updated cell's tile
        Tile *updatedCellTile = get(xIdx,yIdx)->getTile();
        // grab the adjacency list of the cell
        Cell **adjacencyArray = getAdjacencyArray(xIdx,yIdx);
        // bool to handle return at the end
        bool changedAnyEntropy = false;
        // run through the adjacent cells
        for(int i = 0; i < 8; i++){
            Cell *currCell = adjacencyArray[i];
            // check not nullptr cell in adjacency
            if(currCell!=nullptr){
                // check if propagating has change
                if(currCell->propagateNearbyTile(updatedCellTile))
                    changedAnyEntropy=true;
            }
        }
        // done return our tracking bool
        return changedAnyEntropy;
    }

    /**
     * @brief handles collapsing the next cell
     * 
     * PRE: somewhere in the lattice we have entropy
     * POST: handled a collapse and any needed propagation for the collapse
     * 
     */
    void collapseNext(){
        // nominate a cell by grabbing lowest entropy cell at random
        Cell *nominatedCell = getLowestEntropyCell();
        int x = nominatedCell->getCol();
        int y = nominatedCell->getRow();
        // check if collapsing has an update
        if(collapse(x,y))
            propagate(x,y);
        else
            cout << "collapse didn't need to propagate" << endl;
    }
    
    /**
     * @brief loops until all cells collapsed
     *          handing off to `collapseNext()`
     *          for each iteration
     */
    void buildLattice(){
        // collapse all cells till none left with entropy
        while(hasEntropy())
            collapseNext();
        // tell everyone we're done building
        builtGrid = true;
    }

    /**
     * @brief paints a frame of lattice
     * 
     */
    void paint(){
        // build grid if needed
        if(!builtGrid)
            buildLattice();
        // paint the cells
        for(int x = 0; x<colCount; x++)
            for(int y = 0; y < rowCount; y++)
                get(x,y)->paint();
    }

    private:
    // our cell grid
    int xPos;
    int yPos;
    Cell*** cells;
    int colCount;
    int rowCount;
    int cellSize;
    bool builtGrid;
};
