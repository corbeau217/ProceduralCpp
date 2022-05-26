

/**
 * @brief this is what determines what the weight for a regions tiles are
 * 
 * maybe use as a stack/queue for determining a tile's weight
 * 
 */
class PlacementWeight {
    private:
    PlacementOption appliesToOption;
    double placementWeight;
};

/**
 * @brief needs to handle having PlacementOption as child, or Tile
 * 
 * 
 */
class PlacementOption {
    //TODO
};