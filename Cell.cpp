#include "Tile.cpp"


/**
 * @brief this is the cell that goes into lattice
 * 
 * 
 * TODO: need to find a way to say an empty cell for "nulls"
 *          maybe just have a bool that's called like "isInLattice"
 * 
 */
class Cell {
    public:
    // constructor
    Cell(){
        // TODO : default constructor
    }
    Cell(int xIn, int yIn, int sIn, int colIn, int rowIn) {
            x = xIn;
            y = yIn;
            width = sIn;
            height = sIn;
            col = colIn;
            row = rowIn;
        }
    Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn) {
            x = xIn;
            y = yIn;
            width = wIn;
            height = hIn;
            col = colIn;
            row = rowIn;
    }
    // destructor
    ~Cell(){
        //TODO
    }

    /**
     * @brief : choose random option available out of the tile options
     * 
     * @return true : if there was any change that would need propagation
     * @return false : no change due to error or due to no need
     */
    bool collapseOptions(){
        //TODO
        return false;
    }

    /**
     * @brief check if there's any options for this cell
     * 
     * @return true : there's at least one option this cell can choose
     * @return false : if no options / already collapsed this cell
     */
    bool hasOptions(){
        // TODO
        return false;
    }

    /**
     * @brief Set the Tile object
     * 
     * @param t : tile object
     */
    void setTile(Tile *t){
        // TODO
    }

    /**
     * @brief returns how many options this cell has
     * 
     * @return int : -1 if already set, otherwise returns the option count
     */
    int getEntropy(){
        //TODO
        return 0;
    }



    private:
    // drawing variables
    int x;
    int y;
    int width;
    int height;
    // lattice variables
    int col;
    int row;
    //int layer; //would be used when 3d
    // these are for tile options
    Tile* tile;
};