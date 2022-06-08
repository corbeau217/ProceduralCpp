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

#define FRAMESTOCOOLDOWNREROLL FRAMERATE*2.5


/**
 * @brief main app code
 * 
 * 
 */


int appWidth;
int appHeight;
int leftMargin;
int topMargin;
bool recentlyPressedSpace;
bool libSetup;
bool initWindowDone;
int framesSinceReroll;
string appTitle;
Lattice *grid;

int getWidth(){
    return appWidth;
}
int getHeight(){
    return appHeight;
}

/**
 * @brief called in setupApp() if window doesnt exist
 * 
 */
void makeWindow(){
    InitWindow( getWidth(), getHeight(), appTitle.c_str());
    SetTargetFPS( FRAMERATE );
    initWindowDone = true;
}

/**
 * @brief called in setupApp() if a window already exists
 * 
 */
void updateWindow(){
    SetWindowTitle(appTitle.c_str());
}

/**
 * @brief called in setupApp() if lib isnt setup
 * 
 */
void initLib(){
    Lib::setup();
    libSetup = true;
}

void setupApp(){
    cout << "--> Setting up app" << endl;
    
    if (!libSetup)
        initLib();
    // else
    //     *Lib::newGenerateOnClose = false;
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

    appTitle  = "Procedural C++ map, seed: ";
    appTitle += to_string(Lib::getSeed());

    if(!initWindowDone)
        makeWindow();
    else
        updateWindow();
}

void framePaint(){
    ClearBackground(GRAY);
    grid->paint();
    if(recentlyPressedSpace){
        if(framesSinceReroll < 1)
            recentlyPressedSpace = false;
        else
            --framesSinceReroll;
    }
}

void cleanupApp(){
    cout << "Cleaning up app" << endl;
    Lib::closingApp();
    //TODO
    cout << "[nothing to report in cleanup lel]" << endl
            << "[slap a TODO here]"                 << endl;
}

void handleReroll(){
    recentlyPressedSpace = true;
    framesSinceReroll = FRAMESTOCOOLDOWNREROLL;
    cout << "[REROLLING LATTICE]" << endl;
    Lib::handleRerollLattice();
    setupApp();
}

void drawLoop(){
    cout << "--> Starting Main::drawLoop()" << endl;
    // handles the draw loop
    while( !WindowShouldClose() ){
        if(IsKeyDown(KEY_SPACE) && !recentlyPressedSpace)
            handleReroll();
        BeginDrawing();
        framePaint();
        EndDrawing();
    }
    cleanupApp();
}

void startApp(){
    setupApp();
    drawLoop();
    cleanupApp();
    // if(Lib::isResurrectionEnabled())
    //     startApp();
}

int main(){// main landing point
    cout << "--> Executing Main::main()" << endl;
    recentlyPressedSpace = false;
    libSetup = false;
    initWindowDone = false;
    startApp();
    return 0;
}
