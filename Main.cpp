#include "raylib.h"
#include "Lattice.cpp"
#include <iostream>

using namespace std;

#define FRAMERATE 15

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
    // setup our ammounts
    leftMargin = 15;
    topMargin = 15;
    int colCount = 20;
    int rowCount = 20;
    int cellSize = 35;
    // this sets up the app
    appWidth = leftMargin*2 + cellSize*colCount;
    appHeight = topMargin*2 + cellSize*rowCount;
    // setup the grid
    grid = new Lattice(leftMargin,topMargin,colCount,rowCount,cellSize);

    InitWindow( getWidth(), getHeight(), "Procedural C++");
    SetTargetFPS( FRAMERATE );
}

void framePaint(){
    ClearBackground(GRAY);
    // grid->paint();
}

void drawLoop(){
    cout << "--> Starting Main::drawLoop()" << endl;
    // handles the draw loop
    while( !WindowShouldClose() ){
        BeginDrawing();
        framePaint();
        EndDrawing();
    }
}

void cleanupApp(){
    cout << "Cleaning up app" << endl;
    //TODO
    cout << "[nothing to report in cleanup lel]" << endl
            << "[slap a TODO here]"                 << endl;
}

int main(){// main landing point
    cout << "--> Executing Main::main()" << endl;
    setupApp();
    drawLoop();
    cleanupApp();
    return 0;
}
