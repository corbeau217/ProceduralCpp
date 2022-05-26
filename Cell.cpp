#include "Tile.cpp"

class Cell {
    public:
    // constructor
    // Cell(){
    //     // default constructor, we get junked later anyway
    // }
    Cell(int xIn, int yIn, int sIn, int colIn, int rowIn) {
            x = xIn;
            y = yIn;
            width = sIn;
            height = sIn;
            col = colIn;
            row = rowIn;
        }
    Cell(int xIn, int yIn, int wIn, int hIn, int colIn, int rowIn) {
            x = xIn;
            y = yIn;
            width = wIn;
            height = hIn;
            col = colIn;
            row = rowIn;
    }
    // destructor
    ~Cell(){
        //TODO
    }

    



    private:
    // drawing variables
    int x;
    int y;
    int width;
    int height;
    // lattice variables
    int col;
    int row;
    //int layer; //would be used when 3d
    // these are for tile options
    Tile* tile;
};