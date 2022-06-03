#include "Lattice.hpp"
#include <iostream>

using namespace std;



TileList *Lattice::tiles = nullptr;

/**
 * @brief try with using array of indexes for dealing with things or using an array of Cell pointers
 * 
 */

// constructor
Lattice::Lattice(int xLoc, int yLoc, int colCountIn, int rowCountIn, int cellSizeIn) {
    cout << "--> [setting up]: Lattice object" << endl;

    xPos = xLoc;
    yPos = yLoc;
    colCount = colCountIn;
    rowCount = rowCountIn;
    totalCells = colCount*rowCount;
    filledCells = 0;
    cellSize = cellSizeIn;
    // have a colCount length array of Cell** 
    cout << "--> [Generating]: cells pointer array" << endl;
    cells = new Cell**[colCount];
    for(int idx = 0; idx < colCount; idx++){
        // each Cell* is rowCount of Cell*
        cells[idx] = new Cell*[rowCount];
        for(int idx2 = 0; idx2 < rowCount; idx2++)
            cells[idx][idx2] = nullptr;
    }
    builtGrid = false;

    cout << "--> [Generating]: cell objects" << endl;
    // loop through our Cell pointers
    for(int x = 0; x < colCount; x++){
        for(int y = 0; y < rowCount; y++){
            // get our relative position
            int cellXPos = xPos + x*cellSize;
            int cellYPos = yPos + y*cellSize;
            // make the cell
            cells[x][y] = new Cell(cellXPos, cellYPos, cellSize, x, y);
        }
    }

    if(Lattice::tiles==nullptr)
        Lattice::buildTileList();

    cout << "--> [Hand off]: going to Cell::cellMain()" << endl;
    Cell::cellMain();
}

// destructor
Lattice::~Lattice(){
    for(int x = 0; x < colCount; x++){
        for(int y = 0; y < rowCount; y++){
                delete cells[x][y];
        }
        delete cells[x];
    }
    delete cells;
    Cell::StaticCleanup();
}

/**
 * @brief checks if there is a valid location with col and row idx
 * 
 * @param col col idx
 * @param row row idx
 * @return true if we can access that location
 * @return false otherwise
 */
bool Lattice::isValidLocation(int col, int row){
    return (col>-1&&row>-1)&&(col<colCount&&row<rowCount);
}

/**
 * @brief : get the cell at col row
 * 
 * @param col : col idx to get from
 * @param row : row idx to get from
 * @return Cell *: pointer to cell
 */
Cell *Lattice::get(int col, int row){
    if(isValidLocation(col,row))
        return cells[col][row];
    return nullptr;
}

/**
 * @brief returns if there's any entropy in the lattice
 * 
 * @return true : if any cell has entropy
 * @return false : otherwise
 */
bool Lattice::hasEntropy(){
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
int Lattice::getLowestEntropy(){
    // start with highest possible
    int lowestEntropy = Lattice::getTileOptionCount();
    // loop through and check for something lower
    for(int x = 0; x < colCount; x++){
        for(int y = 0; y < rowCount; y++){
            int currCellEntropy = get(x,y)->getEntropy();
            // only look for low entropy where we havent set the tile already
            if(currCellEntropy<lowestEntropy && currCellEntropy>0)
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
int Lattice::getHasEntropyCount(int entropyVal){
    // counter for total matching
    int totalOfEntropyAtVal = 0;
    // loop through and check
    for(int x = 0; x < colCount; x++){
        for(int y = 0; y < rowCount; y++){
            int currCellEntropy = get(x,y)->getEntropy();
            if(currCellEntropy==entropyVal)
                ++totalOfEntropyAtVal;
        }
    }
    return totalOfEntropyAtVal;
}

/**
 * @brief Get the count of how many cells have the lowest entropy
 * 
 * @return int : number of cells with lowest entropy
 */
int Lattice::getLowestEntropyCount(){
    // get lowest entropy
    int lowestEntropy = getLowestEntropy();
    return getHasEntropyCount(lowestEntropy);
}

/**
 * @brief Get the Lowest Entropy List object
 * 
 * length of this array can be found by using getLowestEntropyCount()
 */
Cell **Lattice::getLowestEntropyList(){
    // what the lowest entropy is
    int lowestEntropy = getLowestEntropy();
    // to know how many we need to mess with
    int lowestEntropyCount = getHasEntropyCount(lowestEntropy);
    // handle errors before we cry
    if(lowestEntropyCount == 0) return nullptr;
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
Cell *Lattice::getLowestEntropyCell(){
    int lowestEntropyCount = getLowestEntropyCount();
    Cell **lowestEntropyList = getLowestEntropyList();
    // choose a random option and return
    return lowestEntropyList[Seeder::getRandom(lowestEntropyCount)];
}

/**
 * @brief returns index change in direction
 * 
 * @param dir : 0-7 with 0 being up
 * @return int : the change in x index
 */
int Lattice::dirX(int dir){
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
int Lattice::dirY(int dir){
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
Cell **Lattice::getAdjacencyArray(int xIdx, int yIdx){
    // initialise array of cells
    Cell **adjacencyArray = new Cell*[8];
    // loop through the directions
    for(int i = 0; i < 8; i++){
        // add the direction modifier and position
        int x = dirX(i) + xIdx;
        int y = dirY(i) + yIdx;
        // get the cell and dump into array
        adjacencyArray[i] = get(x,y);
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
bool Lattice::collapse(int xIdx, int yIdx){
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
bool Lattice::propagate(int xIdx, int yIdx){
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
void Lattice::collapseNext(){
    // nominate a cell by grabbing lowest entropy cell at random
    Cell *nominatedCell = getLowestEntropyCell();
    int x = nominatedCell->getCol();
    int y = nominatedCell->getRow();
    // // check if collapsing has an update
    // if(collapse(x,y)){
    //     ++filledCells;
    //     propagate(x,y);
    // }
    // else
    //     cout << "collapse didn't need to propagate" << endl;
    collapse(x,y);
    ++filledCells;
    propagate(x,y);
}

/**
 * @brief loops until all cells collapsed
 *          handing off to `collapseNext()`
 *          for each iteration
 */
void Lattice::buildLattice(){
    cout << "--> [Running]: Lattice::buildLattice()" << endl;
    // collapse all cells till none left with entropy
    while(hasEntropy()){
        // use this to keep track of how many are done
        cout << "|| Cells filled: || " << filledCells << '/' << totalCells << endl;
        collapseNext();
    }
    // tell everyone we're done building
    builtGrid = true;
    cout << "--> Done building lattice" << endl;
}

/**
 * @brief paints a frame of lattice
 * 
 */
void Lattice::paint(){
    // build grid if needed
    if(!builtGrid)
        buildLattice();
    // paint the cells
    for(int x = 0; x<colCount; x++)
        for(int y = 0; y < rowCount; y++)
            get(x,y)->paint();
}

/**
 * @brief interface to the static tile list for getting the tile count
 * 
 * @return int 
 */
int Lattice::getTileOptionCount(){
    return Lattice::tiles->getTotalTiles();
}

Tile *Lattice::getTileOption(int idx){
    return Lattice::tiles->getTileOption(idx);
}

/**
 * @brief sets up the tile options
 * 
 */
void Lattice::buildTileList(){
    
    // tell the client we're doing the tiles
    cout << "--> [Setting up]: Lattice::buildTileList()" << endl;

    Lattice::tiles = new TileList(TILEOPTIONS);

    //get a reference
    TileList *tiles = Lattice::tiles;
    
    // Grass
    cout << "--> [Building]: Grass" << endl;
    // tileColor = new Color(0x74b72e);
    tiles->addTileOption( new Tile("Grass", (Color){65,169,76,255}) );
    tiles->getTileOption( TILEIDX_GRASS )
            ->setTileIdx( TILEIDX_GRASS )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Sand
    cout << "--> [Building]: Sand" << endl;
    tiles->addTileOption( new Tile("Sand",(Color){255,255,153,255}) );
    tiles->getTileOption( TILEIDX_SAND )
            ->setTileIdx( TILEIDX_SAND )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Water
    cout << "--> [Building]: Water" << endl;
    tiles->addTileOption( new Tile("Water",(Color){115,215,255,255}) );
    tiles->getTileOption( TILEIDX_WATER )
            ->setTileIdx( TILEIDX_WATER )
            ->setDisallowsAdjacency( TILEIDX_GRASS  )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Ocean
    cout << "--> [Building]: Ocean" << endl;
    tiles->addTileOption( new Tile("Ocean",(Color){30,144,255,255}) );
    tiles->getTileOption( TILEIDX_OCEAN )
            ->setTileIdx( TILEIDX_OCEAN )
            ->setDisallowsAdjacency( TILEIDX_GRASS  )
            ->setDisallowsAdjacency( TILEIDX_SAND   )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_PLAINS );

    // Forest
    cout << "--> [Building]: Forest" << endl;
    tiles->addTileOption( new Tile("Forest",(Color){0,82,33,255}) );
    tiles->getTileOption( TILEIDX_FOREST )
            ->setTileIdx( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_SAND   )
            ->setDisallowsAdjacency( TILEIDX_WATER  )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
            ->setDisallowsAdjacency( TILEIDX_PLAINS );

    // Deep Ocean
    cout << "--> [Building]: Deep Ocean" << endl;
    tiles->addTileOption( new Tile("Deep Ocean",(Color){0,71,100,255}) );
    tiles->getTileOption( TILEIDX_DEEPOCEAN )
            ->setTileIdx( TILEIDX_DEEPOCEAN )
            ->setDisallowsAdjacency( TILEIDX_GRASS   )
            ->setDisallowsAdjacency( TILEIDX_SAND    )
            ->setDisallowsAdjacency( TILEIDX_FOREST  )
            ->setDisallowsAdjacency( TILEIDX_WATER   )
            ->setDisallowsAdjacency( TILEIDX_PLAINS  );

    // Plains
    cout << "--> [Building]: Plains" << endl;
    tiles->addTileOption( new Tile("Plains",(Color){204,235,197,255}) );
    tiles->getTileOption( TILEIDX_PLAINS )
            ->setTileIdx( TILEIDX_PLAINS )
            ->setDisallowsAdjacency( TILEIDX_OCEAN   )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
            ->setDisallowsAdjacency( TILEIDX_FOREST  );

    cout << "--> Done building tiles" << endl;
    

}