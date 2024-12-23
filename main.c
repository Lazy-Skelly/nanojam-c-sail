#include "Utils.h"
#include "Tiles.h"
#include "Camera.h"
#include "Renderer.h"
#include "UI.h"
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
	
	printf("halo");
	int x,y;
	x=50;
	y=20;
	Animated* animations = NULL;
	
	Texture2D texture = LoadTexture("sprites/spritesheet.png");
	Texture2D power[5];
	power[0] = LoadTexture("sprites/rain.png");
	power[1] = LoadTexture("sprites/seed.png");
	power[2] = LoadTexture("sprites/forest.png");
	power[3] = LoadTexture("sprites/jungle.png");
	power[4] = LoadTexture("sprites/earth.png");
	
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
	int money = 300;
	int selected = 0;
	int cost =0;
	
    while (!WindowShouldClose()) {
		//CameraMoveBorder(&camera,800,400);
	//	if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
/*			Vector2 stuff = PickPoint(camera);
			//printf("%f:%f\n",stuff.x,stuff.y);
			CalculateRange(Map,&tiles,stuff.x,stuff.y,6,type);
			FactoryRanges(Map,&tiles);	*/
			//LimitRange(Map,&tiles,BARREN);
	//		}
		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			CameraMove(&camera);
			
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(RAYWHITE);
        Vector2 stuff = PickPoint(camera);
        switch(selected){
        	case 0:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,6,FERTELIZED);
				FactoryRanges(Map,&tiles);
        		LimitRange(Map,&tiles,BARREN);
        		cost = 25;
        		break;
        	case 1:
        		CalculateRange(Map,&tiles,stuff.x,stuff.y,5,GRASS);
        		LimitRange(Map,&tiles,FERTELIZED);
        		cost = 100;
				break;
			case 2:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,4,FOREST);
				LimitRange(Map,&tiles,GRASS);
				cost = 200;
				break;
			case 3:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,4,JUNGLE);
				LimitRange(Map,&tiles,GRASS);
				cost = 200;
				break;
			case 4:
				int x =PickPoint(camera).x;
				int y =PickPoint(camera).y;
				if(!(Map[x][y].Type != FACTORY && Map[x][y].Type != CITY && Map[x][y].Type != CONWATER)){
				cost = 400;
				
				EarthQuake(Map,&tiles,PickPoint(camera).x,PickPoint(camera).y);
//				EarthQuake(Map,&earth,45,21);
				/*	Addframe(Map,&animations,&earth,false);
					AffectMap(Map,&earth);*/
				}
				break;
			default:
							
		}
 	
		AffectedTile* watercheck = NULL;		
		if(counter < 40 ){	
			if(WaterCheck(Map,&watercheck)){
				Addframe(Map,&animations,&watercheck,true);
				money += AffectMap(Map,&watercheck);
				counter++;				
			}	
			
			if(counter ==40){
				AffectedTile* water = NULL;
				WaterInfluence(Map, &water);
				Addframe(Map,&animations,&water,true);
				money += AffectMap(Map,&water);
			}
		} 
		
		if(IsKeyPressed(KEY_ONE)){
			selected =0;
		}else if(IsKeyPressed(KEY_TWO)){
			selected = 1;
		}else if(IsKeyPressed(KEY_THREE)){
			selected = 2;
		}else if(IsKeyPressed(KEY_FOUR)){
			selected = 3;
		}else if(IsKeyPressed(KEY_FIVE)){
			selected = 4;
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
//			EarthQuake(Map,&earth,45,21);
			CheckRuins(Map,&ruin);
			Addframe(Map,&animations,&ruin,false);
			AffectMap(Map,&ruin);
		}	
		
			
/*		if(type == GRASS){
			CalculateRange(Map,&tiles,x,y,3,type);
			LimitRange(Map,&tiles,FERTELIZED);
		}else{
			CalculateRange(Map,&tiles,x,y,6,type);
			FactoryRanges(Map,&tiles);	
			LimitRange(Map,&tiles,BARREN);
		}*/
//		AffectedTile* temp = tiles;	
		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
			if(money>=cost){
				Addframe(Map,&animations,&tiles,false);
				money += AffectMap(Map,&tiles);
				money -= cost;
			}
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
	/*	DrawRectangle(0,0,50,50,BROWN);
		DrawText(TextFormat("%d",power),20,0,30,YELLOW);*/
		
	/*	if(Button(TextFormat("%d",money),0,0,50,50,50))
			printf("you idiot");*/
		DrawText(TextFormat("%d",money),50,0,25,BLACK);
		ButtonTexture(0,0,50,50,power[selected]);
		for(int i =0;i<5;i++){
			if(ButtonTexture(300+i*50,350,40,40,power[i]))
				selected = i;
			DrawText(TextFormat("%d",i+1),303+i*50,353,15,BLACK);	
		}
		/*if(ButtonTexture(0,0,50,50,texture));
			printf("you idiot");*/	
    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

