#include "Cell.cpp"

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
    


    
    private:

    // our cell grid
    int x;
    int y;
    Cell*** cells;
    int colCount;
    int rowCount;
    int cellSize;
};
