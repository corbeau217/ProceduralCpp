#include "Util.hpp"
#include <string>


using namespace std;


/**
 * @brief converts a string of digits to an unsigned int
 * 
 * @param numberStr : string of digits to convert
 *              [will only convert what will fit in
 *               an unsigned int container]
 * @return unsigned int: of converted value
 */
unsigned *Util::strtou(string numberStr){
    unsigned long resulter = strtoul(numberStr.c_str(), nullptr, 10);
    return new unsigned{(unsigned)resulter};
}


