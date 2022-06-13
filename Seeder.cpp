/**
 * @file Seeder.cpp
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

// include our header
#include "Seeder.hpp"

// --------------------------------------------
// --------------------------------------------
// static
// --------------------------------------------
// declare static variables

Seeder *Seeder::inuse_seed = nullptr;

// --------------------------------------------
// declare static member functions

/**
 * @brief changes the active seed to input param using srand
 * 
 * @param seedToChangeTo 
 */
void Seeder::changeActiveSeed(Seeder *seedToChangeTo){
    // make sure it's declared
    if(seedToChangeTo)
        inuse_seed = seedToChangeTo;
    // now check if we have an active seeder
    if(inuse_seed!=nullptr)
        // then srand() where we want to be
        srand(inuse_seed->getCurrentSeed());
        
}

/**
 * @brief generates the seed iteration, using 
 *      SEED_ITERSTEP_MAX as bounding value
 * 
 * gets the first unsigned value off our seedOrigin_in and
 *      then returns the mod(val,SEED_ITERSTEP_MAX)
 */
unsigned Seeder::generateSeedIterationStep(unsigned seedOrigin_in){
    // change random seed to the seedOrigin_in
    srand(seedOrigin_in);
    // generate a value based off that and return
    return (unsigned)(rand()%SEED_ITERSTEP_MAX);
}

// --------------------------------------------
// --------------------------------------------
// instance
// --------------------------------------------
// declare instance constructors

Seeder::Seeder(){
    // set seedOrigin to DEFAULT_SEED_ORIGIN
    seedOrigin = DEFAULT_SEED_ORIGIN;
    // set our seedStep to DEFAULT_SEED_STEP
    seedStep = DEFAULT_SEED_STEP;
    // set our seedIteration to DEFAULT_SEED_ITER
    seedIteration = DEFAULT_SEED_ITER;
    // now we need to generate the seedStep based off seedOrigin
    seedStep = Seeder::generateSeedIterationStep(seedOrigin);
}
Seeder::Seeder(unsigned seedOrigin_in){
    // set seedOrigin to DEFAULT_SEED_ORIGIN
    seedOrigin = seedOrigin_in;
    // set our seedStep to DEFAULT_SEED_STEP
    seedStep = DEFAULT_SEED_STEP;
    // set our seedIteration to DEFAULT_SEED_ITER
    seedIteration = DEFAULT_SEED_ITER;
    // now we need to generate the seedStep based off seedOrigin
    seedStep = Seeder::generateSeedIterationStep(seedOrigin);
}
Seeder::Seeder(unsigned seedOrigin_in, unsigned seedStep_in, unsigned seedIteration_in){
    // set seedOrigin to DEFAULT_SEED_ORIGIN
    seedOrigin = seedOrigin_in;
    // set our seedStep to DEFAULT_SEED_STEP
    seedStep = seedStep_in;
    // set our seedIteration to DEFAULT_SEED_ITER
    seedIteration = seedIteration_in;
}

// --------------------------------------------
// declare instance destructor

Seeder::~Seeder(){
    //TODO: no pointers to delete yet
}

// --------------------------------------------
// declare instance member functions

/**
 * @brief changes the active seed to this
 * 
 */
void Seeder::makeActive(){
    Seeder::changeActiveSeed(this);
}

/**
 * @brief compare this to otherSeeder
 * 
 * @param otherSeeder 
 * @return true if same
 * @return false otherwise
 */
bool Seeder::equals(Seeder *otherSeeder){
    // check otherSeeder is real
    if(otherSeeder)
        // check it's not nullptr
        if(otherSeeder!=nullptr)
            if(
                    this->seedOrigin    == otherSeeder->seedOrigin
                &&  this->seedStep      == otherSeeder->seedStep
                &&  this->seedIteration == otherSeeder->seedIteration
            )
                return true;
    return false;
}

/**
 * @brief this is for generating the value we use in srand
 * 
 * @return unsigned : value to be put into the c++ srand() func
 */
unsigned Seeder::getCurrentSeed(){
    // the offset from our seedOrigin
    unsigned seedOffset = seedStep * seedIteration;
    // return the new seed to use
    return seedOrigin + seedOffset;
}

/**
 * @brief for getting the unsigned value to use
 * 
 */
unsigned Seeder::getNextRandom(){
    // force this seed to be active, which then redoes srand()
    //      to this->getCurrentSeed()
    makeActive();
    
    // now generate a rand()
    unsigned nextRandom = rand();

    // update our iteration count
    this->seedIteration += 1;

    return nextRandom;
}
