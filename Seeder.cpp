#include "Seeder.hpp"

using namespace std;





/**
 * @brief sets up our randomizing agent with a seed
 * 
 * meant to let us use the same seed again but it doesnt work vry sad
 * 
 */
void Seeder::setup(){
    cout << "--> [Setting up]: Seeder::setup()" << endl;
    long int seed;
    if(Seeder::currSeed==0)
        seed = (long int)time(NULL);
    else
        seed = Seeder::currSeed;
    cout << "|| SEED ||  " << seed << "  || (doesn't do much rn)" << endl;
    srand(seed);

    // srand(time(NULL));
}

/**
 * @brief Get random number within bounding
 * 
 * @param bounding : return is less than this value
 * @return int : value between 0 and bounding
 */
int Seeder::getRandom(int bounding){
    if(bounding == 0)
        return 0;
    int result = rand() % bounding;
    return result;
}