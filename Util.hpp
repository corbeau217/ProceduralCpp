#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <string>


using namespace std;

typedef struct int2D {
    int x;
    int y;
} int2D;

typedef struct rect {
    int x;
    int y;
    int width;
    int height;
} rect;

class Util{
    public:
    /**
     * @brief converts a string of digits to an unsigned int
     * 
     * @param numberStr : string of digits to convert
     *              [will only convert what will fit in
     *               an unsigned int container]
     * @return unsigned int: of converted value
     */
    static unsigned *strtou(string numberStr);

};

#endif
