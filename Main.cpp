#include "raylib.h"
//#include <iostream>



int appWidth;
int appHeight;

int getWidth(){
    return appWidth;
}
int getHeight(){
    return appHeight;
}

void setupApp(){
    // this sets up the app
    appWidth = 500;
    appHeight = 500;
    InitWindow( getWidth(), getHeight(), "Yem");
}

void framePaint(){
    // TODO
    //std::cout << "yem";
    Color bleh;
    bleh = (Color){200,200,200,255};
    DrawCircle(50,50,20,bleh);
}

void drawLoop(){
    // handles the draw loop
    while( !WindowShouldClose() ){
        BeginDrawing();
        framePaint();
        EndDrawing();
    }
}

int main(){// main landing point
    setupApp();
    InitWindow(appWidth,appHeight, "Circle mover"); 
}
