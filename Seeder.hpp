/**
 * @file Seeder.hpp
 * @author corbeau217 (https://github.com/corbeau217)
 * @brief 
 * @version 0.1
 * @date 2022-06-14
 * 
 * https://github.com/corbeau217/cpp_seeder
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// header guard to stop redefining
#ifndef SEEDER_HPP
#define SEEDER_HPP

// c++ includes
#include <time.h>
#include <iostream>
#include <chrono>

// to shorten our definitions
using namespace std;

// default value for seed origin
#define DEFAULT_SEED_ORIGIN (unsigned)time(NULL)
// default value for seed step
#define DEFAULT_SEED_STEP 1
// default value for seed iteration count
#define DEFAULT_SEED_ITER 0

// bounds for how much a seed steps by
#define SEED_ITERSTEP_MAX 100

/**
 * @brief interface for RNG system
 * 
 * this can be bricked if srand() or rand() is called 
 *      seperate to this system so care should be taken
 *      to handle this
 * 
 * error handling could just update it every time we
 *      generate to avoid this instead of checking instead
 * 
 */
class Seeder{
    public:
    // --------------------------------------------
    // --------------------------------------------
    // static
    // --------------------------------------------
    // static variables
    
    // currently active seed
    static Seeder *inuse_seed;

    // --------------------------------------------
    // static member functions

    /**
     * @brief changes the active seed to input param using srand
     * 
     * @param seedToChangeTo 
     */
    static void changeActiveSeed(Seeder *seedToChangeTo);

    /**
     * @brief generates the seed iteration, using 
     *      SEED_ITERSTEP_MAX as bounding value
     * 
     * gets the first unsigned value off our seedOrigin_in and
     *      then returns the mod(val,SEED_ITERSTEP_MAX)
     */
    static unsigned generateSeedIterationStep(unsigned seedOrigin_in);



    // --------------------------------------------
    // --------------------------------------------
    // instance
    // --------------------------------------------
    // instance variables

    // the srand(var)
    unsigned seedOrigin;
    // how much each iteration steps by
    unsigned seedStep;
    // the iteration we're on
    unsigned seedIteration;

    // --------------------------------------------
    // instance constructors/destructor

    // default constructor
    Seeder();

    // construct with seedOrigin_in
    Seeder(unsigned seedOrigin_in);

    // construct with existing information
    Seeder(unsigned seedOrigin_in, unsigned seedStep_in, unsigned seedIteration_in);
    
    // general destructor
    ~Seeder();

    // --------------------------------------------
    // instance member functions

    /**
     * @brief changes the active seed to this
     * 
     */
    void makeActive();

    /**
     * @brief compare this to otherSeeder
     * 
     * handles undefined and nullptr
     * 
     * @param otherSeeder 
     * @return true: if same
     * @return false: otherwise
     */
    bool equals(Seeder *otherSeeder);

    /**
     * @brief this is for generating the value we use in srand
     * 
     * @return unsigned : value to be put into the c++ srand() func
     */
    unsigned getCurrentSeed();

    /**
     * @brief for getting the unsigned value to use
     * 
     */
    unsigned getNextRandom();

};




// end of header guard
#endif