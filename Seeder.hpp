// header guard to stop redefining
#ifndef SEEDER_HPP
#define SEEDER_HPP

#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;


#define CURRENTSEED 0




class Seeder{
    public:
    static unsigned *currSeed;
    
    
    /**
     * @brief sets up our randomizing agent with a seed
     * 
     * meant to let us use the same seed again but it doesnt work vry sad
     * 
     */
    static void setup();

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
    
};

#endif