#include "raylib.h"
#include "Tile.cpp"
#include <iostream>

using namespace std;



namespace tilespc{

    #define TILEOPTIONS 7




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
