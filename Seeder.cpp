#include "Seeder.hpp"

using namespace std;



seedState *Seeder::seed;


/**
 * @brief sets up our randomizing agent with a seed
 * 
 * meant to let us use the same seed again but it doesnt work vry sad
 * 
 */
void Seeder::setup(){
    // setup our asked for seed
    seed = new seedState{nullptr, nullptr};
    seed->seed = new unsigned{CURRENTSEED};
    seed->usage = new unsigned{0U};
    cout << "--> [Setting up]: Seeder::setup()" << endl;
    // if we didnt setup an asked for seed
    if(*seed->seed==0){
        *seed->seed = (unsigned)time(NULL);
        cout << "|| SEED ||--> generated new seed off time  ||" << endl;
    }
    srand(*seed->seed);
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

float Seeder::getFloat(){
    float resulter = (float)rand()/RAND_MAX;
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