#include "raylib.h"


#define TILEOPTIONS 5

class Tile{
    public:
    //constructor
    Tile(char *nameIn) {
        tileName = nameIn;
    }
    //destructor
    ~Tile(){
        //TODO
    }

    /**
     * @brief check if can be near tile
     * 
     * @param t : tile to check
     * @return true : if adjacency allows this
     * @return false : otherwise
     */
    bool canBeNear(Tile *t){
        //TODO
    }

    /**
     * @brief Set cannot be near tile
     * 
     * @param t : tile cant be near
     */
    void setDisallowsAdjacency(Tile *t){
        // TODO
    }

    /**
     * @brief Set the color of this cell
     * 
     * @param c : color to set this tile to use
     */
    void setColor(Color c){
        // TODO
    }

    /**
     * @brief Get the Color object
     * 
     * @return Color* : color of this tile
     */
    Color *getColor(){
        return tileColor;
    }

    private:
    char *tileName;
    Color *tileColor;
};