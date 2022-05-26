#include <cstdio>
#include "raylib.h"




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
    InitWindow(getWidth(),getHeight(),"Yem");
}
void drawLoop(){
    // handles the draw loop
    while(!WindowShouldClose()){
        BeginDrawing();
        //ClearBackground(GRAY);
        EndDrawing();
    }
}
int main(){
    setupApp();
    drawLoop();
}
