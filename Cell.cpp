#include "Tile.cpp"


#define TILEOPTIONS 5

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
            xPos = xIn;
            yPos = yIn;
            width = sIn;
            height = sIn;
            col = colIn;
            row = rowIn;
        }
    Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn) {
            xPos = xIn;
            yPos = yIn;
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
     * @brief checks if we've chosen a tile
     * 
     * @return true : no entropy
     * @return false : otherwise
     */
    bool chosenTile(){
        return getEntropy()==-1;
    }

    /**
     * @brief check if there's any options for this cell
     * 
     * @return true : there's at least one option this cell can choose
     * @return false : if no options / already collapsed this cell
     */
    bool hasOptions(){
        return getEntropy()>0;
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
        if(chosenTile())
            return tile;
        return nullptr;
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
     * @brief : choose random option available out of the tile options
     * 
     * @return true : if there was any change that would need propagation
     * @return false : no change due to error or due to no need
     */
    bool collapse(){
        return false;
    }

    /**
     * @brief handles drawing the frame of the cell
     * 
     */
    void paint(){
        Color *tileColor;
        // try get tile color
        if(chosenTile())
            tileColor = tile->getColor();
        else
            *tileColor = WHITE;
        // draw fill
        DrawRectangle(xPos,yPos,width,height,*tileColor);
        // draw outline
        DrawRectangleLines(xPos,yPos,width,height,BLACK);
    }

    private:
    // drawing variables
    int xPos;
    int yPos;
    int width;
    int height;
    // lattice variables
    int col;
    int row;
    //int layer; //would be used when 3d
    // these are for tile options
    Tile* tile;
};