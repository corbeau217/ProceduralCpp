

class CellCoord {
    public:
    // constructor
    CellCoord(int xIn, int yIn)
        :x{xIn},y{yIn}{}
    
    // comparison operators

    bool operator==(CellCoord other){
        return x==other.x && y==other.y;
    }

    // comparison member functions

    /**
     * @brief compares the x of this to other
     * 
     * @param other coord to compare to
     * @return int : >0 if this.x is further,
     *              0 if this.x is same,
     *              <0 if other.x is further
     */
    int compareX(CellCoord other){
        return x-other.x;
    }
    /**
     * @brief compares the y of this to other
     * 
     * @param other coord to compare to
     * @return int : >0 if this.y is further,
     *              0 if this.y is same,
     *              <0 if other.y is further
     */
    int compareY(CellCoord other){
        return y-other.y;
    }
    
    // arithmetic operator overloading

    // for adding two coordinates
    CellCoord& operator+(CellCoord other){
        CellCoord* output = new CellCoord(x+other.x,y+other.y);
        return *output;
    }
    // for subtracting two coordinates
    CellCoord& operator-(CellCoord other){
        CellCoord* output = new CellCoord(x-other.x,y-other.y);
        return *output;
    }
    // for multiplying two coordinates
    CellCoord& operator*(CellCoord other){
        CellCoord* output = new CellCoord(x*other.x,y*other.y);
        return *output;
    }
    // for divide two coordinates
    CellCoord& operator/(CellCoord other){
        CellCoord* output = new CellCoord(x/other.x,y/other.y);
        return *output;
    }
    // for modulo two coordinates
    CellCoord& operator%(CellCoord other){
        CellCoord* output = new CellCoord(x%other.x,y%other.y);
        return *output;
    }
    
    // other member functions here i guess
    
    private:
    int x;
    int y;
};