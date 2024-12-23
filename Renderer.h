#pragma once
#include "Utils.h"
#include "Tiles.h"


#ifndef HALLO
#define HALLO
extern Rectangle BARRENTEXTURE ;
extern Rectangle FERTILETEXTURE ;
extern Rectangle GRASSTEXTURE;
extern Rectangle FORESTTEXTURE;
extern Rectangle JUNGLETEXTURE;
extern Rectangle CITYTEXTURE;
extern Rectangle FACTORYTEXTURE;
//extern Rectangle CONWATERTEXTURE = {0,0,32,32};
extern Rectangle WATERTEXTURE ;
extern Rectangle RUINTEXTURE ;
extern Rectangle BADWATERTEXTURE ;
extern Rectangle ECORUINTEXTURE ;
#endif

typedef struct Animated{
	int x,y;
	int frame;
	int type;
	struct Animated* next;
}Animated;

typedef struct Cell{
	Texture2D texture;
	int type;
}Cell;



void Draw(Tile Map[WORLDSIZE][WORLDSIZE], Texture2D texture);
Vector2 PickPoint(Camera2D camera);
