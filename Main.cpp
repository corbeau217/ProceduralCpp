#include "Seeder.hpp"
#include "raylib.h"
#include "Lattice.hpp"
#include "Util.hpp"
#include "Lib.hpp"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#define FRAMERATE 15




/**
 * @brief main app code
 * 
 * 
 */


int appWidth;
int appHeight;
int leftMargin;
int topMargin;
Lattice *grid;

int getWidth(){
    return appWidth;
}
int getHeight(){
    return appHeight;
}

void setupApp(){
    cout << "--> Setting up app" << endl;
    // tell lib to setup
    Lib::setup();
    // setup our amounts
    leftMargin = 10;
    topMargin = 10;
    int2D *latticePos = new int2D{
        leftMargin,
        topMargin
    };
    int colCount = 70;
    int rowCount = 40;
    int2D *cellCount = new int2D{
        colCount,
        rowCount
    };
    int cellSize = 18;
    // this sets up the app
    appWidth = leftMargin*2 + cellSize*colCount;
    appHeight = topMargin*2 + cellSize*rowCount;
    // setup the grid
    grid = new Lattice(latticePos,cellCount,cellSize);

    string appTitle  = "Procedural C++ map, seed: ";
    appTitle += to_string(Lib::getSeed());

    InitWindow( getWidth(), getHeight(), appTitle.c_str());
    SetTargetFPS( FRAMERATE );
}

void framePaint(){
    ClearBackground(GRAY);
    grid->paint();
}

void cleanupApp(){
    cout << "Cleaning up app" << endl;
    Lib::closingApp();
    //TODO
    cout << "[nothing to report in cleanup lel]" << endl
            << "[slap a TODO here]"                 << endl;
}

void drawLoop(){
    cout << "--> Starting Main::drawLoop()" << endl;
    // handles the draw loop
    while( !WindowShouldClose() ){
        BeginDrawing();
        framePaint();
        EndDrawing();
    }
    cleanupApp();
}

int main(){// main landing point
    cout << "--> Executing Main::main()" << endl;
    setupApp();
    drawLoop();
    cleanupApp();
    return 0;
}
