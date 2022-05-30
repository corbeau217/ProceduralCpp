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

    int getCol(){
        return col;
    }
    int getRow(){
        return row;
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
     * @brief Get a reference to the tile this cell has
     * 
     * @return Tile* : returns nullptr if still has entropy
     */
    Tile *getTile(){
        if(getEntropy()==-1)
            return tile;
        return nullptr;
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
    bool hasEntropy(){
        return getEntropy()>-1;
    }

    /**
     * @brief this handles collapsing this tile into one of the options it can be
     * 
     * @return true : if there was a change to this tile, requiring propagation
     * @return false : otherwise
     */
    bool collapse(){
        return false;
    }

    /**
     * @brief tell this cell it's nearby a tile
     * 
     * @param t : the tile reference it's nearby
     * @return true : if there was a change to this cell's options
     * @return false : otherwise
     */
    bool propagateNearbyTile(Tile *t){
        //TODO
        return false;
    }

    /**
     * @brief handles drawing the frame of the cell
     * 
     */
    void paint(){
        //TODO
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

    // TODO: use this to tell if we've chose a tile
    bool chosenTile;
};