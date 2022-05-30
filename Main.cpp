#include "raylib.h"
#include "Lattice.cpp"
//#include <iostream>



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
    // setup randoming
    Randoming::setup();
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
    *grid = {leftMargin,topMargin,colCount,rowCount,cellSize};

    InitWindow( getWidth(), getHeight(), "Procedural C++");
}

void framePaint(){
    ClearBackground(GRAY);
    grid->paint();
}

void drawLoop(){
    // handles the draw loop
    while( !WindowShouldClose() ){
        BeginDrawing();
        framePaint();
        EndDrawing();
    }
}

void cleanupApp(){
    //TODO
}

int main(){// main landing point
    setupApp();
    drawLoop();
    cleanupApp();
}
