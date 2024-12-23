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
extern Rectangle CONWATERTEXTURE;
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

typedef struct Building{
	int frame;
	int x,y;
	int type;
	int size;
	Texture2D texture;
	struct Building* next;
}Building;


void Draw(Tile Map[WORLDSIZE][WORLDSIZE], Texture2D texture, Animated** list, AffectedTile** highlight, Building** builds);
void AddAnimated(Animated** list, int x, int y, int type, int frame);
void Addframe(Tile Map[WORLDSIZE][WORLDSIZE],Animated** list, AffectedTile** tiles, bool world);
void DrawSingle(Tile Map[WORLDSIZE][WORLDSIZE],Building** builds,int x, int y, Color color);
void DrawBuilding(Tile Map[WORLDSIZE][WORLDSIZE], Building** builds);
void AddBuilding(Building** builds,int type,int x, int y, int frame, int size, Texture2D texture);
void RemoveBuild(Building** list, int x, int y);
Animated* GetAnimated(Animated** list, int x, int y);
Vector2 PickPoint(Camera2D camera);
