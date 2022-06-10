#include "Util.hpp"
#include "Seeder.hpp"





/**
 * @brief we tryna make a noisy grid of floats i guess
 * 
 * TODO: setup with templates and a function pointer for getting the next element to fill with
 * 
 *      maybe we could set this up with a "doToEach" function that takes a function to apply to every element
 */

class NoisedGrid {
    public:
    float ****grid;
    int2D *dimensions;
    seedState *gridSeed;
    float minimum;
    float maximum;
    float floatPerElem;

    // constructor
    NoisedGrid(int2D *dimensionsIn, 
    float minIn, float maxIn, float elemCountIn){
        // copy dimensions
        dimensions = dimensionsIn;
        floatPerElem = elemCountIn;
        // copy seed
        gridSeed = Seeder::getSeedStateCopy();
        // make array of pointer arrays
        grid = new float***[dimensions->x];
        // loop through each pointer array and add the elements to it
        for(int x = 0; x < dimensions->x; x++){
            grid[x] = new float**[dimensions->y];
            for(int y = 0; y < dimensions->y; y++){
                // set as nullptr for now
                grid[x][y] = new float*[floatPerElem];
                for(int z = 0; z < floatPerElem; z++)
                    grid[x][y][z] = getNextNoisyFloat();

            }
        }
    }
    
    // destructor
    ~NoisedGrid(){
        for(int x = 0; x< dimensions->x; x++){
            for(int y = 0; y < dimensions->y; y++){
                for(int z = 0; z < floatPerElem; z++){
                    delete grid[x][y][z];
                }
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
        float *returnable = new float{
                minimum + Seeder::getFloat(maximum-minimum)
            };
        return returnable;
    }

    /**
     * @brief getters
     * 
     */
    float **get(int2D *loc){
        return grid[loc->x][loc->y];
    }
    float **get(int x, int y){
        return get(new int2D{x,y});
    }
    float *get(int2D *loc, int elem){
        return get(loc)[elem];
    }
    float *get(int x, int y, int z){
        return get(x,y)[z];
    }
};