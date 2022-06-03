#include "TileList.hpp"
#include <iostream>

using namespace std;


//constructor
TileList::TileList(){
    // tell the client we're doing the tiles
    cout << "--> [Setting up]: TileList" << endl;

    // set up variables
    tileOptionsCount = TILEOPTIONS;
    totalAdded = 0;
    // setup pointers
    tileOptions = new Tile*[tileOptionsCount];
    for(int i = 0; i < tileOptionsCount; i++)
        tileOptions[i] = nullptr;
    
    // Grass
    cout << "--> [Building]: Grass" << endl;
    // tileColor = new Color(0x74b72e);
    addTileOption( new Tile("Grass", (Color){65,169,76,255}) );
    getTileOption( TILEIDX_GRASS )
            ->setTileIdx( TILEIDX_GRASS )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Sand
    cout << "--> [Building]: Sand" << endl;
    addTileOption( new Tile("Sand",(Color){255,255,153,255}) );
    getTileOption( TILEIDX_SAND )
            ->setTileIdx( TILEIDX_SAND )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Water
    cout << "--> [Building]: Water" << endl;
    addTileOption( new Tile("Water",(Color){115,215,255,255}) );
    getTileOption( TILEIDX_WATER )
            ->setTileIdx( TILEIDX_WATER )
            ->setDisallowsAdjacency( TILEIDX_GRASS  )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  );

    // Ocean
    cout << "--> [Building]: Ocean" << endl;
    addTileOption( new Tile("Ocean",(Color){30,144,255,255}) );
    getTileOption( TILEIDX_OCEAN )
            ->setTileIdx( TILEIDX_OCEAN )
            ->setDisallowsAdjacency( TILEIDX_GRASS  )
            ->setDisallowsAdjacency( TILEIDX_SAND   )
            ->setDisallowsAdjacency( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_PLAINS );

    // Forest
    cout << "--> [Building]: Forest" << endl;
    addTileOption( new Tile("Forest",(Color){0,82,33,255}) );
    getTileOption( TILEIDX_FOREST )
            ->setTileIdx( TILEIDX_FOREST )
            ->setDisallowsAdjacency( TILEIDX_SAND   )
            ->setDisallowsAdjacency( TILEIDX_WATER  )
            ->setDisallowsAdjacency( TILEIDX_OCEAN  )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
            ->setDisallowsAdjacency( TILEIDX_PLAINS );

    // Deep Ocean
    cout << "--> [Building]: Deep Ocean" << endl;
    addTileOption( new Tile("Deep Ocean",(Color){0,71,100,255}) );
    getTileOption( TILEIDX_DEEPOCEAN )
            ->setTileIdx( TILEIDX_DEEPOCEAN )
            ->setDisallowsAdjacency( TILEIDX_GRASS   )
            ->setDisallowsAdjacency( TILEIDX_SAND    )
            ->setDisallowsAdjacency( TILEIDX_FOREST  )
            ->setDisallowsAdjacency( TILEIDX_WATER   )
            ->setDisallowsAdjacency( TILEIDX_PLAINS  );

    // Plains
    cout << "--> [Building]: Plains" << endl;
    addTileOption( new Tile("Plains",(Color){204,235,197,255}) );
    getTileOption( TILEIDX_PLAINS )
            ->setTileIdx( TILEIDX_PLAINS )
            ->setDisallowsAdjacency( TILEIDX_OCEAN   )
            ->setDisallowsAdjacency( TILEIDX_DEEPOCEAN  )
            ->setDisallowsAdjacency( TILEIDX_FOREST  );

    cout << "--> Done building tiles" << endl;

}
//destructor
TileList::~TileList(){
    for(int i = 0; i < tileOptionsCount; i++)
        delete tileOptions[i];
    delete tileOptions;
}




Tile *TileList::getTileOption(int idx){
    return tileOptions[idx];
}

void TileList::addTileOption(Tile *t){
    if(totalAdded<tileOptionsCount){
        tileOptions[totalAdded] = t;
        ++totalAdded;
    }
}

int TileList::getTotalTiles(){
    return TILEOPTIONS;
}
