#include "Util.hpp"
#include "raylib.h"
#include "Seeder.hpp"
#include <math.h>

/**
 * @brief this is basically just perlin noise generator
 * 
 * 
 * honestly lets just make it the basic early one first 
 *      bc that makes sense
 * 
 */
class NoisedGrid {
    public:
    // seed while making
    Seeder *gridSeed;
    // grid of vectors
    Vector2 ***perlinVectors;

    int2D *dimensions; // pixel width/height

    // constructor
    NoisedGrid(int2D *resolutionDimensions, int grad_period_in, unsigned seed_val){
        // copy dimensions
        dimensions = resolutionDimensions;
        // copy seed
        gridSeed = new Seeder(seed_val);
        // make array of pointer arrays
        perlinVectors = new Vector2**[dimensions->x];
        // loop through each pointer array and add the elements to it
        for(int x = 0; x < dimensions->x; x++){
            perlinVectors[x] = new Vector2*[dimensions->y];
            for(int y = 0; y < dimensions->y; y++){
                // set as nullptr for now
                perlinVectors[x][y] = nullptr;
            }
        }
    }
    
    // destructor
    ~NoisedGrid(){
        for(int x = 0; x< dimensions->x; x++){
            for(int y = 0; y < dimensions->y; y++){
                delete perlinVectors[x][y];
            }
            delete perlinVectors[x];
        }
        delete perlinVectors;
        delete dimensions;
        delete gridSeed;
    }

    /**
     * @brief Get the next noisy float var
     * 
     */
    Vector2 *getNextNoisyGradient(){
        Vector2 *returnable =nullptr;
        *returnable = {0,0}; //TODO
        return returnable;
    }

    /**
     * @brief getters
     * 
     * @param loc int2D of the location to get
     * @return float* returned element pointer
     */
    Vector2 *get(int2D *loc){
        return perlinVectors[loc->x][loc->y];
    }
    Vector2 *get(int x, int y){
        return get(new int2D{x,y});
    }
};