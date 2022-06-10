#include "Util.hpp"
#include "raylib.h"
#include "Seeder.hpp"

/**
 * @brief this is basically just perlin noise generator
 * 
 */
class NoisedGrid {
    public:
    // seed while making
    seedState *gridSeed;
    // grid of vectors
    Vector2 ***grid;
    
    int2D *dimensions; // pixel width/height

    // constructor
    NoisedGrid(int2D *dimensionsIn){
        // copy dimensions
        dimensions = dimensionsIn;
        // copy seed
        gridSeed = Seeder::getSeedStateCopy();
        // make array of pointer arrays
        grid = new float**[dimensions->x];
        // loop through each pointer array and add the elements to it
        for(int x = 0; x < dimensions->x; x++){
            grid[x] = new float*[dimensions->y];
            for(int y = 0; y < dimensions->y; y++){
                // set as nullptr for now
                grid[x][y] = nullptr;
                grid[x][y] = getNextNoisyFloat();

            }
        }
    }
    
    // destructor
    ~NoisedGrid(){
        for(int x = 0; x< dimensions->x; x++){
            for(int y = 0; y < dimensions->y; y++){
                delete grid[x][y];
            }
            delete grid[x];
        }
        delete grid;
        delete dimensions;
        delete gridSeed;
    }

    /**
     * @brief Get the next noisy float var
     * 
     */
    float *getNextNoisyFloat(){
        float *returnable =nullptr;
        *returnable = 0; //TODO
        return returnable;
    }

    /**
     * @brief getters
     * 
     * @param loc int2D of the location to get
     * @return float* returned element pointer
     */
    float *get(int2D *loc){
        return grid[loc->x][loc->y];
    }
    float *get(int x, int y){
        return get(new int2D{x,y});
    }
};