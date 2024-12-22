#include "Utils.h"
#include "Tiles.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 400

Tile Map[64][64];

int main(void){
    InitWindow(WIDTH,HEIGHT,"RayLibussy");
    SetTargetFPS(60);
	
	ReinitializeMap(Map);
	AffectedTile* tiles = NULL;
//	DeleteTile(&tiles,1,0);
//	AffectMap(Map,&tiles);
	
/*	while(tiles){
		printf("%d ",tiles->x);
		AffectedTile* temp = tiles->Next;
		free(tiles);
		tiles = temp;
	}*/
	Map[46][20].Type = FACTORY;
	Map[45][21].Type = FACTORY;
	Map[46][21].Type = FACTORY;
	Map[45][20].Type = FACTORY;

	Map[10][20].Type = FACTORY;
	Map[10][21].Type = FACTORY;
	Map[10][22].Type = FACTORY;
	Map[10][22].Type = FACTORY;

	Map[30][22].Type = RUIN;
	Map[30][22].Type = RUIN;
	
	Map[20][22].Type = WATER;
	Map[20][23].Type = WATER;
	Map[20][24].Type = WATER;
	Map[20][25].Type = WATER;
	Map[20][26].Type = WATER;
	Map[21][26].Type = WATER;
	Map[20][27].Type = WATER;
	Map[21][27].Type = WATER;
	Map[20][28].Type = WATER;
	Map[21][28].Type = WATER;
	Map[20][29].Type = WATER;
	Map[21][29].Type = WATER;
	Map[21][30].Type = WATER;
	Map[21][31].Type = WATER;
	Map[21][32].Type = WATER;
	Map[21][33].Type = WATER;
	Map[21][34].Type = WATER;	
	
	printf("halo");
	int x,y;
	x=50;
	y=20;
	int type = FERTELIZED;
	
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
		if(IsKeyPressed(KEY_DOWN))
			y++;
		if(IsKeyPressed(KEY_UP))
			y--;
		if(IsKeyPressed(KEY_LEFT))
			x--;
		if(IsKeyPressed(KEY_RIGHT))
			x++;	
					
		if(IsKeyPressed(KEY_C)){
			type = GRASS;
			AffectedTile* water = NULL;
			WaterInfluence(Map, &water);
			AffectMap(Map,&water);
		}
		
		if(IsKeyPressed(KEY_X)){
			AffectedTile* earth = NULL;
			EarthQuake(Map,&earth,45,20);
//			EarthQuake(Map,&earth,45,21);
			AffectMap(Map,&earth);
		}
		
		if(IsKeyPressed(KEY_V)){
			AffectedTile* ruin = NULL;
			CheckRuins(Map,&ruin);
//			EarthQuake(Map,&earth,45,21);
			AffectMap(Map,&ruin);
		}	
			
		if(type == GRASS){
			CalculateRange(Map,&tiles,x,y,3,type);
			LimitRange(Map,&tiles,FERTELIZED);
		}else{
			CalculateRange(Map,&tiles,x,y,6,type);
			FactoryRanges(Map,&tiles);	
			LimitRange(Map,&tiles,BARREN);
		}
//		AffectedTile* temp = tiles;	
		AffectMap(Map,&tiles);
//		AffectedTile* factory;
/*		CalculateRange(Map,&factory,45,20,5,BARREN);
		while(factory){
//			DrawRectangle(factory->x*5+20,factory->y*5+20,5,5,GREEN);
			DeleteTile(&tiles,factory->x,factory->y);
//			temp = temp->Next;
			AffectedTile* temp = factory->Next;
			free(factory);
			factory = temp;
		}*/
		while(tiles){
			DrawRectangle(tiles->x*5+20,tiles->y*5+20,5,5,BLUE);
//			temp = temp->Next;
			AffectedTile* temp = tiles->Next;
			free(tiles);
			tiles = temp;
		}
		DrawMap(Map);
    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

