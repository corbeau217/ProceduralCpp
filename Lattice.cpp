#include "Cell.cpp"


/**
 * @brief try with using array of indexes for dealing with things or using an array of Cell pointers
 * 
 */
class Lattice{
    public:
    // constructor
    Lattice(int xLoc, int yLoc, int colCountIn, int rowCountIn, int cellSizeIn) {

        x = xLoc;
        y = yLoc;
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
     * @return Cell& : reference to cell
     */
    Cell& get(int col, int row){
        if(isValidLocation(col,row))
            return *cells[col][row];
        
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
        //TODO
        return 0;
    }

    /**
     * @brief Get the Lowest Entropy List object
     * 
     * length of this array can be found by using getLowestEntropyCount()
     */
    Cell **getLowestEntropyList(){
        // TODO
    }

    /**
     * @brief Get a list of the adjacent cells
     * 
     * @param xIdx : the index of x to get from
     * @param yIdx : the index of y to get from
     * length is always 8
     */
    Cell **getAdjacencyArray(int xIdx, int yIdx){
        // TODO
    }

    /**
     * @brief Get the cell with the lowest entropy in a given list
     * 
     * @return Cell& : address of the cell
     */
    Cell& getLowestEntropyCell(){
        //TODO
    }

    /**
     * @brief Get the count of how many cells have the lowest entropy
     * 
     * @return int : number of cells with lowest entropy
     */
    int getLowestEntropyCount(){
        return 0;
    }

    /**
     * @brief Get lowest entropy in the lattice
     * 
     * @return int : lowest entropy number
     */
    int getLowestEntropy(){
        //TODO
        return 0;
    }

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-8 with 0 being up
     * @return int : the change in x index
     */
    int dirX(int dir){
        return 0;
    }

    /**
     * @brief returns index change in direction
     * 
     * @param dir : 0-8 with 0 being up
     * @return int : the change in y index
     */
    int dirY(int dir){
        return 0;
    }



    private:
    // our cell grid
    int x;
    int y;
    Cell*** cells;
    int colCount;
    int rowCount;
    int cellSize;
};
