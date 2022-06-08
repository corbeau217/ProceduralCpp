// header guard to stop redefining
#ifndef SEEDER_HPP
#define SEEDER_HPP

#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;


#define CURRENTSEED 0



typedef struct seedState {
    unsigned *seed;
    unsigned *usage;
} seedState;

class Seeder{
    public:
    static seedState *seed;
    
    
    /**
     * @brief sets up our randomizing agent with a seed
     * 
     * 
     */
    static void setup(unsigned seedIn);

    /**
     * @brief Get random number within bounding
     * 
     * @param bounding : return is less than this value
     * @return int : value between 0 and bounding
     */
    static int getRandom(int bounding);

    /**
     * @brief returns float between 0 and 1
     * 
     * @return float 
     */
    static float getFloat();

    /**
     * @brief returns to a point in the line of a particular seed
     * 
     */
    static void returnToSeed(unsigned seed, unsigned usage);
    static void returnToSeed(seedState *seed);

    /**
     * @brief gets pointer for information about the current seed
     * 
     */
    static seedState *getSeedStateCopy();
    
};


#endif