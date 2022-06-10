#include "Seeder.hpp"

using namespace std;



seedState *Seeder::seed;


/**
 * @brief sets up our randomizing agent with a seed
 * 
 * meant to let us use the same seed again but it doesnt work vry sad
 * 
 */
void Seeder::setup(unsigned seedIn){
    // setup our asked for seed
    seed = new seedState{
            new unsigned{seedIn},
            new unsigned{0U}
        };
    // say we're setting up
    cout << "--> [Setting up]: Seeder::setup()" << endl;
    srand(*seed->seed);

    // say in console for copypasta
    cout << "|| SEED ||  " << *seed->seed << "U  ||" << endl;

}


/**
 * @brief Get random number within bounding
 * 
 * @param bounding : return is less than this value
 * @return int : value between 0 and bounding
 */
int Seeder::getRandom(int bounding){

    int resulter = rand() % bounding;
    ++*seed->usage;
    //cout << "["<< resulter <<"]["<< bounding <<"]" <<endl;
    return resulter;
}

float Seeder::getFloat(float maximum){
    float resulter = (float)rand()/RAND_MAX*maximum;
    ++*seed->usage;
    return resulter;
}

/**
 * @brief returns to a point in the line of a particular seed
 * 
 */
void Seeder::returnToSeed(unsigned seedIn, unsigned usage){
    // change our seed
    *seed->seed = seedIn;
    // srand it
    srand(*seed->seed);
    // reset our uses
    *seed->usage = 0U;
    // spam them out until we reach our usage
    while(*seed->usage < usage)
        getRandom(0);
}
void Seeder::returnToSeed(seedState *seedIn){
    returnToSeed(*seedIn->seed, *seedIn->usage);
}

/**
 * @brief gets pointer for information about the current seed
 * 
 */
seedState *Seeder::getSeedStateCopy(){
    return new seedState{seed->seed, seed->usage};
}