#include "raylib.h"
#include <iostream>

using namespace std;



namespace tilespc{

    #define TILEOPTIONS 5

    #define TILEIDX_GRASS 0
    #define TILEIDX_SAND 1
    #define TILEIDX_WATER 2
    #define TILEIDX_OCEAN 3
    #define TILEIDX_FOREST 4

    /**
     * @brief this is the tiles that we can use
     * 
     * 
     */
    class Tile{
        public:
        int tileIdx;


        //constructor
        // Tile(){
        //     tileIdx = -1;
        //     tileName = "Tile";
        //     canBeNearTile = new bool[TILEOPTIONS];
        //     setColor(WHITE);
        // }
        Tile(const char *nameIn) {
            tileIdx = -1;
            tileName = nameIn;
            canBeNearTile = new bool[TILEOPTIONS];
            tileColor = WHITE;
        }
        Tile(const char *nameIn, Color colorIn) {
            tileIdx = -1;
            tileName = nameIn;
            canBeNearTile = new bool[TILEOPTIONS];
            setColor(colorIn);
        }
        //destructor
        ~Tile(){
            delete canBeNearTile;
            delete tileName;
        }

        /**
         * @brief Get the index of this tile
         * 
         * @return int : returns -1 if no tile index was set
         */
        int getTileIdx(){
            return tileIdx;
        }
        /**
         * @brief Set the Tile index
         * 
         * @param idx : index to set it to
         * 
         * has builder pattern
         */
        Tile *setTileIdx(int idx){
            tileIdx = idx;
            return this;
        }

        bool canBeNear(int idx){
            return canBeNearTile[idx];
        }
        /**
         * @brief check if can be near tile
         * 
         * @param t : tile to check
         * @return true : if adjacency allows this
         * @return false : otherwise
         * PRE: t was setup with valid tile index
         */
        bool canBeNear(Tile *t){
            return canBeNear(t->getTileIdx());
        }

        Tile *setDisallowsAdjacency(int idx){
            canBeNearTile[idx] = false;
            return this;
        }
        /**
         * @brief Set cannot be near tile
         * 
         * @param t : tile cant be near
         * PRE: t was setup with valid tile index
         */
        Tile *setDisallowsAdjacency(Tile *t){
            return setDisallowsAdjacency(t->getTileIdx());
        }

        /**
         * @brief Set the color of this cell
         * 
         * @param c : color to set this tile to use
         * 
         * has builder pattern
         */
        Tile *setColor(Color c){
            tileColor = c;
            return this;
        }


        /**
         * @brief Get the Color object
         * 
         * @return Color* : color of this tile
         */
        Color *getColor(){
            return &tileColor;
        }





        private:
        bool *canBeNearTile;
        const char *tileName;
        Color tileColor;

    };


    static Tile **tileOptions;

    // ===================================================
    
    /**
     * @brief sets up the tile options
     * 
     */
    static void setupTileOptions(){
        // tell the client we're doing the tiles
        cout << "--> [Setting up]: Tile::setupTileOptions()" << endl;

        cout << "--> [Creating]: tileOptions array" << endl;
        tileOptions = new Tile*[TILEOPTIONS];

        // Grass
        cout << "--> [Building]: Grass" << endl;
        tileOptions[TILEIDX_GRASS] = new Tile("Grass",GREEN);
        tileOptions[TILEIDX_GRASS]
                ->setTileIdx( TILEIDX_GRASS )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  );

        // Sand
        cout << "--> [Building]: Sand" << endl;
        tileOptions[TILEIDX_SAND] = new Tile("Sand",YELLOW);
        tileOptions[TILEIDX_SAND]
                ->setTileIdx( TILEIDX_SAND )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  )
                ->setDisallowsAdjacency( TILEIDX_FOREST );

        // Water
        cout << "--> [Building]: Water" << endl;
        tileOptions[TILEIDX_WATER] = new Tile("Water",BLUE);
        tileOptions[TILEIDX_WATER]
                ->setTileIdx( TILEIDX_WATER )
                ->setDisallowsAdjacency( TILEIDX_GRASS  )
                ->setDisallowsAdjacency( TILEIDX_FOREST );

        // Ocean
        cout << "--> [Building]: Ocean" << endl;
        tileOptions[TILEIDX_OCEAN] = new Tile("Ocean",DARKBLUE);
        tileOptions[TILEIDX_OCEAN]
                ->setTileIdx( TILEIDX_OCEAN )
                ->setDisallowsAdjacency( TILEIDX_GRASS  )
                ->setDisallowsAdjacency( TILEIDX_SAND   )
                ->setDisallowsAdjacency( TILEIDX_FOREST );

        // Forest
        cout << "--> [Building]: Forest" << endl;
        tileOptions[TILEIDX_FOREST] = new Tile("Forest",DARKGREEN);
        tileOptions[TILEIDX_FOREST]
                ->setTileIdx( TILEIDX_FOREST )
                ->setDisallowsAdjacency( TILEIDX_SAND   )
                ->setDisallowsAdjacency( TILEIDX_WATER  )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  );

        cout << "--> Done building tiles" << endl;
    }

    /**
     * @brief effectively the static destructor
     * 
     */
    static void staticCleanup(){
        delete tileOptions;
    }

    static Tile *getTileOption(int idx){
        return tileOptions[idx];
    }
}
