#include "raylib.h"
#include <iostream>

using namespace std;



namespace tilespc{

    #define TILEOPTIONS 7


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
            for(int i = 0; i < TILEOPTIONS; i++)
                canBeNearTile[i] = true;
            tileColor = WHITE;
        }
        Tile(const char *nameIn, Color colorIn) {
            tileIdx = -1;
            tileName = nameIn;
            canBeNearTile = new bool[TILEOPTIONS];
            for(int i = 0; i < TILEOPTIONS; i++)
                canBeNearTile[i] = true;
            tileColor = colorIn;
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
    static const int tileOptionsCount = TILEOPTIONS;

    // ===================================================
    
    #define TILEIDX_GRASS 0
    #define TILEIDX_SAND 1
    #define TILEIDX_WATER 2
    #define TILEIDX_OCEAN 3
    #define TILEIDX_FOREST 4
    #define TILEIDX_DEEPOCEAN 5
    #define TILEIDX_PLAINS 6

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
        // tileColor = new Color(0x74b72e);
        tileOptions[TILEIDX_GRASS] = new Tile("Grass", (Color){65,169,76,255});
        tileOptions[TILEIDX_GRASS]
                ->setTileIdx( TILEIDX_GRASS )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  )
                ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

        // Sand
        cout << "--> [Building]: Sand" << endl;
        tileOptions[TILEIDX_SAND] = new Tile("Sand",(Color){255,255,153,255});
        tileOptions[TILEIDX_SAND]
                ->setTileIdx( TILEIDX_SAND )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  )
                ->setDisallowsAdjacency( TILEIDX_FOREST )
                ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

        // Water
        cout << "--> [Building]: Water" << endl;
        tileOptions[TILEIDX_WATER] = new Tile("Water",(Color){115,215,255,255});
        tileOptions[TILEIDX_WATER]
                ->setTileIdx( TILEIDX_WATER )
                ->setDisallowsAdjacency( TILEIDX_GRASS  )
                ->setDisallowsAdjacency( TILEIDX_FOREST )
                ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

        // Ocean
        cout << "--> [Building]: Ocean" << endl;
        tileOptions[TILEIDX_OCEAN] = new Tile("Ocean",(Color){30,144,255,255});
        tileOptions[TILEIDX_OCEAN]
                ->setTileIdx( TILEIDX_OCEAN )
                ->setDisallowsAdjacency( TILEIDX_GRASS  )
                ->setDisallowsAdjacency( TILEIDX_SAND   )
                ->setDisallowsAdjacency( TILEIDX_FOREST )
                ->setDisallowsAdjacency( TILEIDX_PLAINS );

        // Forest
        cout << "--> [Building]: Forest" << endl;
        tileOptions[TILEIDX_FOREST] = new Tile("Forest",(Color){0,82,33,255});
        tileOptions[TILEIDX_FOREST]
                ->setTileIdx( TILEIDX_FOREST )
                ->setDisallowsAdjacency( TILEIDX_SAND   )
                ->setDisallowsAdjacency( TILEIDX_WATER  )
                ->setDisallowsAdjacency( TILEIDX_OCEAN  )
                ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
                ->setDisallowsAdjacency( TILEIDX_PLAINS );

        // Deep Ocean
        cout << "--> [Building]: Deep Ocean" << endl;
        tileOptions[TILEIDX_DEEPOCEAN] = new Tile("Deep Ocean",(Color){0,71,100,255});
        tileOptions[TILEIDX_DEEPOCEAN]
                ->setTileIdx( TILEIDX_DEEPOCEAN )
                ->setDisallowsAdjacency( TILEIDX_GRASS   )
                ->setDisallowsAdjacency( TILEIDX_SAND    )
                ->setDisallowsAdjacency( TILEIDX_FOREST  )
                ->setDisallowsAdjacency( TILEIDX_WATER   )
                ->setDisallowsAdjacency( TILEIDX_PLAINS  );

        // Plains
        cout << "--> [Building]: Plains" << endl;
        tileOptions[TILEIDX_PLAINS] = new Tile("Plains",(Color){204,235,197,255});
        tileOptions[TILEIDX_PLAINS]
                ->setTileIdx( TILEIDX_PLAINS )
                ->setDisallowsAdjacency( TILEIDX_OCEAN   )
                ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
                ->setDisallowsAdjacency( TILEIDX_FOREST  );

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
