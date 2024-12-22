#pragma once
#include "Utils.h"
#define BARREN 0 
#define FERTELIZED 1 
#define GRASS 2 
#define FOREST 3 
#define JUNGLE 4 
#define CITY 5 
#define FACTORY 6 
#define CONWATER 7 
#define WATER 8 
#define RUIN 9
#define BADWATER 10
#define ECORUIN 11

#define FACTORYINFLUENCE 5
#define EARTHQUAKE 3 

#define WORLDSIZE 64

typedef struct Tile{
	int Type; //grass, factor, road, fertilized, grass .....
	
}Tile;

typedef struct AffectedTile{
	int x,y;
	int Type;
	struct AffectedTile* Next;
}AffectedTile;

void ReinitializeMap(Tile Map[WORLDSIZE][WORLDSIZE]);
void AffectMap(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles);
void AddTile(AffectedTile** tiles ,int x, int y, int type);
bool SearchList(AffectedTile** tiles,int x, int y);
void CalculateRange(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int x, int y, int Power, int type);
void DeleteTile(AffectedTile** tiles, int x, int y);
void FactoryRanges(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles);
void LimitRange(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int type);
void WaterInfluence(Tile Map[WORLDSIZE][WORLDSIZE],AffectedTile** tiles);
void EarthQuake(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int x, int y);
void CheckRuins(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** ruin);
//just testing 
void DrawMap(Tile Map[WORLDSIZE][WORLDSIZE]);
