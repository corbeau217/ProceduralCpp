#include "Cell.cpp"



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
     * @brief collapse at location, return if we need to propagate
     * 
     * @param xIdx : the index of x to collapse
     * @param yIdx : the index of y to collapse
     * @return true : changed the cell and need to propagate
     * @return false : no change/error
     */
    bool collapse(int xIdx, int yIdx){
        // TODO
        return false;
    }
    
    /**
     * @brief propagate changes to a cell
     * 
     * @param xIdx : the index of x to propagate
     * @param yIdx : the index of y to propagate
     * @return true : if there was a change in entropy of any cell
     * @return false : if no change to entropy of any cell
     */
    bool propagate(int xIdx, int yIdx){
        //TODO 
        return false;
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
     * @brief paints a frame of lattice
     * 
     */
    void paint(){
        //TODO
    }

    private:
    // our cell grid
    int xPos;
    int yPos;
    Cell*** cells;
    int colCount;
    int rowCount;
    int cellSize;
};
