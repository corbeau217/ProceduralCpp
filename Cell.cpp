#include "Tile.cpp"
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;

#define TILEOPTIONCOUNT 7

#define CURRENTSEED 0




class RandomSeeder{
    public:
    static const long int currSeed = CURRENTSEED;
    
    /**
     * @brief sets up our randomizing agent with a seed
     * 
     * meant to let us use the same seed again but it doesnt work vry sad
     * 
     */
    static void setup(){
        cout << "--> [Setting up]: RandomSeeder::setup()" << endl;
        long int seed;
        if(currSeed==0)
            seed = (long int)time(NULL);
        else
            seed = currSeed;
        cout << "|| SEED ||  " << seed << "  || (doesn't do much rn)" << endl;
        srand(seed);

        // srand(time(NULL));
    }

    /**
     * @brief Get random number within bounding
     * 
     * @param bounding : return is less than this value
     * @return int : value between 0 and bounding
     */
    static int getRandom(int bounding){
        if(bounding == 0)
            return 0;
        int result = rand() % bounding;
        return result;
    }
    
};

/**
 * @brief this is the cell that goes into lattice
 * 
 * 
 * TODO: need to find a way to say an empty cell for "nulls"
 *          maybe just have a bool that's called like "isInLattice"
 * 
 * 
 * TODO: have each cell setup with an array of tile options and then
 *          just modify that list during propagation/collapsing
 * 
 */
class Cell {
    public:
    // constructor
    // Cell(){
    //     // TODO : default constructor
    // }
    Cell(int xIn, int yIn, int sIn, int colIn, int rowIn) {
            tileSet = false;
            xPos = xIn;
            yPos = yIn;
            width = sIn;
            height = sIn;
            col = colIn;
            row = rowIn;
            canBeTile = new bool[tilespc::tileOptionsCount];
            for(int i = 0; i < tilespc::tileOptionsCount; i++)
                canBeTile[i] = true;
            tile = nullptr;
        }
    Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn) {
            tileSet = false;
            xPos = xIn;
            yPos = yIn;
            width = wIn;
            height = hIn;
            col = colIn;
            row = rowIn;
            canBeTile = new bool[tilespc::tileOptionsCount];
            for(int i = 0; i < tilespc::tileOptionsCount; i++)
                canBeTile[i] = true;
            tile = nullptr;
    }
    // destructor
    ~Cell(){
        delete tile;
        delete canBeTile;
    }


    int getCol(){
        return col;
    }
    int getRow(){
        return row;
    }

    /**
     * @brief checks if we've chosen a tile
     * 
     * @return true : no entropy
     * @return false : otherwise
     */
    bool chosenTile(){
        return tileSet;
    }

    /**
     * @brief returns how many options this cell has
     * 
     * @return int : -1 if already set, otherwise returns the option count
     * 
     * TODO: check if this behaves correctly with empty tile reference, might need null tiles
     */
    int getEntropy(){
        if(chosenTile())
            return -1;
        int counter = 0;
        for(int i = 0; i < tilespc::tileOptionsCount; i++)
            if(canBeTile[i])
                ++counter;
        return counter;
    }
    bool hasEntropy(){
        return !chosenTile() && getEntropy()>0;
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
    void setTile(tilespc::Tile *t){
        tile = t;
        for(int i = 0; i < tilespc::tileOptionsCount; i++)
            canBeTile[i] = false;
        tileSet = true;
    }

    /**
     * @brief Get a reference to the tile this cell has
     * 
     * @return Tile* : returns nullptr if still has entropy
     */
    tilespc::Tile *getTile(){
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
    bool propagateNearbyTile(tilespc::Tile *t){
        bool didWeModify = false;
        // loop through all tile options
        for(int i = 0; i < tilespc::tileOptionsCount; i++){
            if(canBeTile[i]){
                //store if we can be near
                canBeTile[i] = tilespc::getTileOption(i)->canBeNear(t);
                if(!canBeTile[i])
                    // suddenly we cant, mark that there was an update
                    didWeModify = true;
            }
        }
        return didWeModify;
    }

    /**
     * @brief : choose random option available out of the tile options
     * 
     * @return true : if there was any change that would need propagation
     * @return false : no change due to error or due to no need
     */
    bool collapse(){
        // get how many options we can be
        int optionCount = getEntropy();
        if(optionCount<1) // no options return false
            return false;
        // otherwise we choose an option randomly
        int randomExistingOption = RandomSeeder::getRandom(optionCount);
        // loop through our options to find the one we chose
        for(int i = 0, k = 0; i < tilespc::tileOptionsCount; i++){
            // check is valid option
            if(canBeTile[i]){
                // check random number
                if(k==randomExistingOption){
                    //we found our option, collapse to this one
                    setTile(tilespc::getTileOption(i));
                    return true;
                }
                ++k;
            }
        }
        return false;
    }

    /**
     * @brief handles drawing the frame of the cell
     * 
     */
    void paint(){
        Color tileColor;
        // try get tile color
        if(chosenTile())
            tileColor = *(tile->getColor());
        else
            tileColor = WHITE;
        // draw fill
        DrawRectangle(xPos,yPos,width,height,tileColor);
        // draw outline
        DrawRectangleLines(xPos,yPos,width,height,(Color){20,20,20,255});
    }



    /**
     * @brief static handle for cell
     * 
     */
    static void cellMain(){
        cout << "--> [Setting up]: Cell::cellMain()" << endl;

        // setup RandomSeeder
        cout << "--> [Hand off]: going to RandomSeeder::setup()" << endl;
        RandomSeeder::setup();
        // setup tile options
        cout << "--> [Hand off]: going to Tile::setupTileOptions()" << endl;
        tilespc::setupTileOptions();
    }

    static void StaticCleanup(){
        //TODO: delete the static stuffs
        tilespc::staticCleanup();
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
    // these are for tile option
    tilespc::Tile* tile;
    // keeps track of whether we've set this to have a tile yet
    bool tileSet;
    // keep track of what tiles we can be
    bool* canBeTile;
};


