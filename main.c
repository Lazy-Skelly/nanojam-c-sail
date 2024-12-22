#include "Utils.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 400

int main(void){
    InitWindow(WIDTH,HEIGHT,"RayLibussy");
    SetTargetFPS(60);
	
	
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);



    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

