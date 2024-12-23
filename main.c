#include "Utils.h"
#include "Tiles.h"
#include "Camera.h"
#include "Renderer.h"
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 400

Tile Map[64][64];


/* TODO (#1#): continue animation you got the idea wxith the 
               struct go for it */

bool ColorIsEqual(Color col, Color col2){
	return col.r == col2.r && col.g == col2.g && col.b == col.b;
}

int main(void){
    InitWindow(WIDTH,HEIGHT,"Kirby");
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
/*	Map[46][20].Type = FACTORY;
	Map[45][21].Type = FACTORY;
	Map[46][21].Type = FACTORY;
	Map[45][20].Type = FACTORY;

	Map[10][20].Type = FACTORY;
	Map[10][21].Type = FACTORY;
	Map[10][22].Type = FACTORY;
	Map[10][22].Type = FACTORY;

	Map[30][22].Type = RUIN;
	Map[30][23].Type = RUIN;
	
	Map[25][22].Type = CONWATER;
	
	Map[20][22].Type = BADWATER;
	Map[20][23].Type = BADWATER; 
	Map[20][24].Type = BADWATER;
	Map[20][25].Type = BADWATER;
	Map[20][26].Type = BADWATER;
	Map[21][26].Type = BADWATER;
	Map[20][27].Type = BADWATER;
	Map[21][27].Type = BADWATER;
	Map[20][28].Type = BADWATER;
	Map[21][28].Type = BADWATER;
	Map[20][29].Type = BADWATER;
	Map[21][29].Type = BADWATER;
	Map[21][30].Type = BADWATER;
	Map[21][31].Type = BADWATER;
	Map[21][32].Type = BADWATER;
	Map[21][33].Type = BADWATER;
	Map[21][34].Type = BADWATER;	*/
	
	printf("halo");
	int x,y;
	x=50;
	y=20;
	int type = FERTELIZED;
	
	Animated* animations = NULL;
	
	Texture2D texture = LoadTexture("sprites/spritesheet.png");
	Rectangle source= {0,0,32,32};
	Image image = LoadImage("sprites/map.png");
	Color* color = LoadImageColors(image);
/*	printf("%d,%d,%d\n",color[0].r,color[0].g,color[0].b);
	printf("%d,%d,%d\n",color[1].r,color[1].g,color[1].b);
	printf("%d,%d,%d\n",color[2].r,color[2].g,color[2].b);
	printf("%d,%d,%d\n",color[3].r,color[3].g,color[3].b);
	printf("%d,%d,%d\n",color[4].r,color[4].g,color[4].b);*/
	Building* builds = NULL;
	for(int i = 0; i< WORLDSIZE;i++){
		for(int j =0;j < WORLDSIZE;j++){
			if(ColorIsEqual(color[i*64+j],(Color){172,50,50,0})){
				Map[i][j].Type = BARREN;
			}else if(ColorIsEqual(color[i*64+j],(Color){0,0,0,0})){
				Map[i][j].Type = FACTORY;
				if(Map[i-1][j].Type == BARREN && Map[i][j-1].Type == BARREN){
					AddBuilding(&builds,FACTORY,i,j,0,1,LoadTexture("sprites/Factory.png"));
				}
			}else if(ColorIsEqual(color[i*64+j],(Color){251,242,54,0})){
				Map[i][j].Type = CITY;
				AddBuilding(&builds,CITY,i,j,0,rand()%4,LoadTexture("sprites/City.png"));
			}else if(ColorIsEqual(color[i*64+j],(Color){91,110,225,0})){
				Map[i][j].Type = BADWATER;
			}else if(ColorIsEqual(color[i*64+j],(Color){255,255,255,0})){
				Map[i][j].Type = CONWATER;
				AddBuilding(&builds,CONWATER,i,j,0,42,LoadTexture("sprites/ConWater.png"));
			}else{
				Map[i][j].Type = GRASS;
			}
		}
	}
	Building* temp = NULL;
	while(builds){
		Building* smth = NULL;
		smth = builds->next;
		builds->next = temp;
		temp = builds;
		builds = smth;
	}
	builds = temp;
	
	Camera2D camera ;
	camera.offset = (Vector2){0,0}; 
	camera.target = (Vector2){0,0};
	camera.zoom = 1;
	camera.rotation = 0; 
	
	int counter = 0;
	
    while (!WindowShouldClose()) {
		//CameraMoveBorder(&camera,800,400);
	//	if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
			Vector2 stuff = PickPoint(camera);
			//printf("%f:%f\n",stuff.x,stuff.y);
			CalculateRange(Map,&tiles,stuff.x,stuff.y,6,type);
			FactoryRanges(Map,&tiles);	
			//LimitRange(Map,&tiles,BARREN);
	//		}
		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			CameraMove(&camera);
			
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(RAYWHITE);
        
       // DrawTexture(texture,0,0,WHITE);
       	/*for(int i = 0; i<25;i++){
    		for(int j = 0;j<25;j++){
				DrawTexturePro(texture,source,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}
		}*/
		
		
		
		if(IsKeyPressed(KEY_DOWN))
			y++;
		if(IsKeyPressed(KEY_UP))
			y--;
		if(IsKeyPressed(KEY_LEFT))
			x++;
		if(IsKeyPressed(KEY_RIGHT))
			x--;	
		
		AffectedTile* watercheck = NULL;
		
		if(IsKeyPressed(KEY_E)){
			Map[25][22].Type = RUIN;
		}
		
		if(counter < 90 ){	
			if(WaterCheck(Map,&watercheck)){
				Addframe(Map,&animations,&watercheck,true);
				AffectMap(Map,&watercheck);
				type = GRASS;
				counter++;				
			}	
			
			if(counter ==90){
				AffectedTile* water = NULL;
				WaterInfluence(Map, &water);
				Addframe(Map,&animations,&water,true);
				AffectMap(Map,&water);
			}
		} 
		
		if(IsKeyPressed(KEY_B)){
			type = FOREST;
		}
		
		if(IsKeyPressed(KEY_N)){
			type = JUNGLE;
		}
		
		if(IsKeyPressed(KEY_X)){
			AffectedTile* earth = NULL;
			int x =PickPoint(camera).x;
			int y =PickPoint(camera).y;
			if(!(Map[x][y].Type != FACTORY && Map[x][y].Type != CITY && Map[x][y].Type != CONWATER)){
			
				
				EarthQuake(Map,&earth,PickPoint(camera).x,PickPoint(camera).y);
//				EarthQuake(Map,&earth,45,21);
				Addframe(Map,&animations,&earth,false);
				AffectMap(Map,&earth);
			}
		}
		
		if(IsKeyPressed(KEY_V)){
			AffectedTile* ruin = NULL;
			CheckRuins(Map,&ruin);
//			EarthQuake(Map,&earth,45,21);
			Addframe(Map,&animations,&ruin,false);
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
		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
			Addframe(Map,&animations,&tiles,false);
			AffectMap(Map,&tiles);
		}
		
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
		Draw(Map,texture,&animations,&tiles,&builds);
//		DrawBuilding(Map,&builds); 
		while(tiles){
		//	DrawRectangle(tiles->x*5+20,tiles->y*5+20,5,5,BLUE);
//			temp = temp->Next;
			AffectedTile* temp = tiles->Next;
			free(tiles);
			tiles = temp;
		}
		//DrawMap(Map);
		EndMode2D();
		DrawRectangle(0,0,10,10,RED);
    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

