#include "raylib.h"


#define TILEOPTIONS 5

#define GRASS 0
#define SAND 1
#define WATER 2
#define DEEPWATR 3
#define FOREST 4

/**
 * @brief this is the tiles that we can use
 * 
 * 
 */
class Tile{
    public:
    int tileIdx;

    //constructor
    Tile(char *nameIn) {
        tileIdx = -1;
        tileName = nameIn;
        canBeNearTile = new bool[TILEOPTIONS];
        setColor(WHITE);
    }
    Tile(char *nameIn, Color colorIn) {
        tileIdx = -1;
        tileName = nameIn;
        canBeNearTile = new bool[TILEOPTIONS];
        setColor(colorIn);
    }
    //destructor
    ~Tile(){
        delete canBeNearTile;
        delete tileColor;
        delete tileName;
    }

    /**
     * @brief Get the index of this tile
     * 
     * @return int : returns -1 if no tile index was set
     */
    int getTileIdx(){
        return tileIdx;
    }
    /**
     * @brief Set the Tile index
     * 
     * @param idx : index to set it to
     * 
     * has builder pattern
     */
    Tile *setTileIdx(int idx){
        tileIdx = idx;
        return this;
    }

    bool canBeNear(int idx){
        return canBeNearTile[idx];
    }
    /**
     * @brief check if can be near tile
     * 
     * @param t : tile to check
     * @return true : if adjacency allows this
     * @return false : otherwise
     * PRE: t was setup with valid tile index
     */
    bool canBeNear(Tile *t){
        canBeNear(t->getTileIdx());
    }

    Tile *setDisallowsAdjacency(int idx){
        canBeNearTile[idx] = false;
        return this;
    }
    /**
     * @brief Set cannot be near tile
     * 
     * @param t : tile cant be near
     * PRE: t was setup with valid tile index
     */
    Tile *setDisallowsAdjacency(Tile *t){
        setDisallowsAdjacency(t->getTileIdx());
        return this;
    }

    /**
     * @brief Set the color of this cell
     * 
     * @param c : color to set this tile to use
     * 
     * has builder pattern
     */
    Tile *setColor(Color c){
        *tileColor = c;
        return this;
    }


    /**
     * @brief Get the Color object
     * 
     * @return Color* : color of this tile
     */
    Color *getColor(){
        return tileColor;
    }


    // ===================================================


    /**
     * @brief sets up the tile options
     * 
     */
    static void setupTileOptions(){
        tileOptions = new Tile*[TILEOPTIONS];

        // grass
        tileOptions[GRASS] = new Tile("Grass",GREEN);
        tileOptions[GRASS]->setTileIdx(GRASS)->setDisallowsAdjacency(DEEPWATR);

        // sand
        tileOptions[SAND] = new Tile("Sand",YELLOW);
        tileOptions[SAND]->setTileIdx(SAND)->setDisallowsAdjacency(DEEPWATR)->setDisallowsAdjacency(FOREST);

        // water
        tileOptions[WATER] = new Tile("Water",BLUE);
        tileOptions[WATER]->setTileIdx(WATER)->setDisallowsAdjacency(GRASS)->setDisallowsAdjacency(FOREST);

        // deep water
        tileOptions[DEEPWATR] = new Tile("Deep Water",DARKBLUE);
        tileOptions[DEEPWATR]->setTileIdx(DEEPWATR)->setDisallowsAdjacency(GRASS)->setDisallowsAdjacency(SAND)->setDisallowsAdjacency(FOREST);

        // forest
        tileOptions[FOREST] = new Tile("Forest",DARKGREEN);
        tileOptions[FOREST]->setTileIdx(FOREST)->setDisallowsAdjacency(SAND)->setDisallowsAdjacency(WATER)->setDisallowsAdjacency(DEEPWATR);

    }

    /**
     * @brief effectively the static destructor
     * 
     */
    static void staticCleanup(){
        delete tileOptions;
    }

    static Tile *getTileOption(int idx){
        return tileOptions[idx];
    }

    private:
    bool *canBeNearTile;
    char *tileName;
    Color *tileColor;

    static Tile **tileOptions;
};