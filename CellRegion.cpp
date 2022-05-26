#include "CellList.cpp"


/**
 * @brief this is what is used to divie out the cells for populating/propagating/filling an area
 * 
 * CellRegion may have CellRegion(s) as children
 * 
 * use this to replace CellList
 * 
 */
class CellRegion {
    // TODO

    /**
     * @brief Get the Region object
     *      maybe have this as returning the region that cell location is in
     * 
     * @param x index
     * @param y index
     * @return CellRegion& region object
     */
    CellRegion& getRegion(int x, int y){
        // TODO
    }
    CellRegion& nominateSuperposition(){
        // TODO
    }
    bool collapse(CellRegion *cr){
        // TODO
    }
    /**
     * @brief for checking if any superpositions of children or this region
     * 
     * @return true if any children have superposition still
     * @return false otherwise
     */
    bool isSuperposition(){
        // TODO
    }

};