#include "Seeder.hpp"

using namespace std;



unsigned *Seeder::currSeed;


/**
 * @brief sets up our randomizing agent with a seed
 * 
 * meant to let us use the same seed again but it doesnt work vry sad
 * 
 */
void Seeder::setup(){
    // setup our asked for seed
    Seeder::currSeed = new unsigned{CURRENTSEED};
    cout << "--> [Setting up]: Seeder::setup()" << endl;
    unsigned seed;
    // if we didnt setup an asked for seed
    if(*Seeder::currSeed==0){
        seed =  (unsigned)time(NULL);
        cout << "|| SEED ||--> generated new seed off time  ||" << endl;
    }
    else
        seed = *Seeder::currSeed;
    srand(seed);
    cout << "|| SEED ||  " << seed << "U  ||" << endl;

    // srand(time(NULL));
}

/**
 * @brief Get random number within bounding
 * 
 * @param bounding : return is less than this value
 * @return int : value between 0 and bounding
 */
int Seeder::getRandom(int bounding){
    int resulter = rand() % bounding;
    //cout << "["<< resulter <<"]["<< bounding <<"]" <<endl;
    return resulter;
}

float Seeder::getFloat(){
    return (float)rand()/RAND_MAX;
}