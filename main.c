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

bool StartMenuBefore(Texture2D Start,int height,int width){
    Rectangle s;
    s.height=(float)Start.height;
    s.width=(float)Start.width;
    s.x=0;
    s.y=0;
    Rectangle v;
    v.height=(float)height;
    v.width=(float)width;
    v.x=0;
    v.y=0;
    Vector2 f={0,0};

    //DrawTexture(Start,0,0,WHITE);
    DrawTexturePro(Start,s,v,f,0.0f,WHITE);
    return true;
}

int main(void){
    InitWindow(WIDTH,HEIGHT,"Kirby");
    InitAudioDevice();   
    SetTargetFPS(60);
	
	ReinitializeMap(Map);
	AffectedTile* tiles = NULL;
	
	printf("halo");
	int x,y;
	x=50;
	y=20;
	Animated* animations = NULL;
	
	Sound ost = LoadSound("sprites/Light on a Window.mp3");
	Sound over = LoadSound("sprites/Game Over.mp3");
	Sound sounds[5] ;
	Sound water = LoadSoundFromWave(LoadWave("sprites/water.wav"));
	sounds[0] = LoadSoundFromWave(LoadWave("sprites/magic.wav"));
	sounds[1] = LoadSoundFromWave(LoadWave("sprites/grass.wav"));
	sounds[2] = LoadSoundFromWave(LoadWave("sprites/forest.wav"));
	sounds[3] = LoadSoundFromWave(LoadWave("sprites/forest.wav"));
	sounds[4] = LoadSoundFromWave(LoadWave("sprites/crash.wav"));
	
	Texture2D texture = LoadTexture("sprites/spritesheet.png");
	Texture2D menu = LoadTexture("sprites/DEFOREST.png");
	Texture2D mommy = LoadTexture("sprites/dommymommy.png");
	Texture2D dommy = LoadTexture("sprites/Dommymommydissapointedinyou.png");
	Texture2D power[5];
	power[0] = LoadTexture("sprites/rain.png");
	power[1] = LoadTexture("sprites/seed.png");
	power[2] = LoadTexture("sprites/forest.png");
	power[3] = LoadTexture("sprites/jungle.png");
	power[4] = LoadTexture("sprites/earth.png");
	
	Texture2D bildingz[3];
	bildingz[0] = LoadTexture("sprites/Factory.png");
	bildingz[1] = LoadTexture("sprites/City.png");
	bildingz[2] = LoadTexture("sprites/ConWater.png");
	
	Rectangle source= {0,0,32,32};
	Image image = LoadImage("sprites/maptutorialp.png");
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
					AddBuilding(&builds,FACTORY,i,j,0,1,bildingz[0]);
				}
			}else if(ColorIsEqual(color[i*64+j],(Color){251,242,54,0})){
				Map[i][j].Type = CITY;
				AddBuilding(&builds,CITY,i,j,0,rand()%4,bildingz[1]);
			}else if(ColorIsEqual(color[i*64+j],(Color){91,110,225,0})){
				Map[i][j].Type = BADWATER;
			}else if(ColorIsEqual(color[i*64+j],(Color){255,255,255,0})){
				Map[i][j].Type = CONWATER;
				AddBuilding(&builds,CONWATER,i,j,0,42,bildingz[2]);
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
	camera.target = (Vector2){-379,212};
	camera.zoom = 1;
	camera.rotation = 0; 
	
	int counter = 0;
	int money = 300000;
	int selected = 0;
	int cost =0;
	int strength =0;
	int talk = 26;
	int talkcounter = 0;
	int choice = 1;
	int overcounter =0;
	bool Do = false;
	SetMasterVolume(0.25);
	SetExitKey(KEY_NULL);
	
    while (!WindowShouldClose()) {
    	if(!IsSoundPlaying(ost) && talk != 28){
    		StopSound(over);
    		PlaySound(ost);
		}else if (talk == 28){
			StopSound(ost);
			if(!IsSoundPlaying(over))
				PlaySound(over);
		}
		
		if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && talk == 27)
			CameraMove(&camera);
		FixCamera(&camera);	
			
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(DARKGRAY);
        Vector2 stuff ;
        switch(talk){
        	case 4:
        		stuff = (Vector2){41,17};
				break;	 
        	case 5:
        		stuff = (Vector2){41,17};
				break;	
			case 6:
        		stuff = (Vector2){41,17};
				break;
			case 7:
        		stuff = (Vector2){41,17};
				break;	
			case 8:
        		stuff = (Vector2){38,17};
				break;
			case 9:
        		stuff = (Vector2){38,17};
				break;
			case 10:
        		stuff = (Vector2){44,17};
				break;
			case 11:
        		stuff = (Vector2){44,17};
				break;
			case 13:
        		stuff = (Vector2){10,30};
				break;
			case 14:
        		stuff = (Vector2){10,30};
				break;
			case 16:
        		stuff = (Vector2){9,4};
				break;
			case 17:
        		stuff = (Vector2){9,4};
				break;
			case 18:
        		stuff = (Vector2){7,7};
				break;
			case 19:
        		stuff = (Vector2){7,7};
				break;
			case 20:
        		stuff = (Vector2){9,4};
				break;	
			case 21:
        		stuff = (Vector2){9,4};
				break;
			case 23:
        		stuff = (Vector2){41,40};
				break;
			case 24:
        		stuff = (Vector2){41,40};
				break;
			case 27:
        		stuff = PickPoint(camera);
				break;													 
        	default:
        		stuff.x = 10000000000;
        		stuff.y = 10000000000;
        		
		}
        switch(selected){
        	case 0:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,6+strength,FERTELIZED);
				FactoryRanges(Map,&tiles);
        		LimitRange(Map,&tiles,BARREN);
        		cost = 25;
        		break;
        	case 1:
        		CalculateRange(Map,&tiles,stuff.x,stuff.y,5+strength,GRASS);
        		LimitRange(Map,&tiles,FERTELIZED);
        		cost = 100;
				break;
			case 2:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,4+strength,FOREST);
				LimitRange(Map,&tiles,GRASS);
				cost = 200;
				break;
			case 3:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,4+strength,JUNGLE);
				LimitRange(Map,&tiles,GRASS);
				cost = 200;
				break;
			case 4:
				int x =stuff.x;
				int y =stuff.y;
				if(!(Map[x][y].Type != FACTORY && Map[x][y].Type != CITY && Map[x][y].Type != CONWATER)){
					cost = 400;
					EarthQuake(Map,&tiles,x,y);
				}
				break;
			default:							
		}
		
 		if(talk == 26){
 			Do = false;
 			Image image = LoadImage(TextFormat("sprites/map%d.png",choice));
			Color* color = LoadImageColors(image);	
		//	Building* builds = NULL;
			while(builds){
				Building* temp = builds->next;
				free(builds);
				builds = temp;
			}
		for(int i = 0; i< WORLDSIZE;i++){
			for(int j =0;j < WORLDSIZE;j++){
				if(ColorIsEqual(color[i*64+j],(Color){172,50,50,0})){
					AddTile(&tiles,i,j,BARREN);
				}else if(ColorIsEqual(color[i*64+j],(Color){0,0,0,0})){
					AddTile(&tiles,i,j,FACTORY);
				}else if(ColorIsEqual(color[i*64+j],(Color){251,242,54,0})){
					AddTile(&tiles,i,j,CITY);
				}else if(ColorIsEqual(color[i*64+j],(Color){91,110,225,0})){
					AddTile(&tiles,i,j,BADWATER);
				}else if(ColorIsEqual(color[i*64+j],(Color){255,255,255,0})){
					AddTile(&tiles,i,j,CONWATER);
				}else{
					AddTile(&tiles,i,j,GRASS);
				}
			}
		}
			talk++;
			PlaySound(sounds[selected]);
			counter = 0;
			Addframe(Map,&animations,&tiles,true);
			AffectMap(Map,&tiles);
			money = 30;
			selected =0;
		for(int i = 0; i< WORLDSIZE;i++){
			for(int j =0;j < WORLDSIZE;j++){
				if(ColorIsEqual(color[i*64+j],(Color){172,50,50,0})){
				}else if(ColorIsEqual(color[i*64+j],(Color){0,0,0,0})){
					if(Map[i-1][j].Type == BARREN && Map[i][j-1].Type == BARREN){
						AddBuilding(&builds,FACTORY,i,j,0,1,bildingz[0]);
					}
				}else if(ColorIsEqual(color[i*64+j],(Color){251,242,54,0})){
					AddBuilding(&builds,CITY,i,j,0,rand()%4,bildingz[1]);
				}else if(ColorIsEqual(color[i*64+j],(Color){91,110,225,0})){
				}else if(ColorIsEqual(color[i*64+j],(Color){255,255,255,0})){
					AddBuilding(&builds,CONWATER,i,j,0,42,bildingz[2]);
				}
			}
		}
		UnloadImage(image);
		}
 		
		AffectedTile* watercheck = NULL;		
		if(counter < 40 ){	
			if(WaterCheck(Map,&watercheck)){
				Addframe(Map,&animations,&watercheck,true);
				money += AffectMap(Map,&watercheck);
				counter++;
			}
			if(counter==1){
				PlaySound(water);				
			}	
			
			if(counter ==40){
				AffectedTile* water = NULL;
				WaterInfluence(Map, &water);
				Addframe(Map,&animations,&water,true);
				money += AffectMap(Map,&water);
				PlaySound(sounds[3]);
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
			printf("%f,%f\n",camera.target.x,camera.target.y);
			printf("mouse %f,%f\n",PickPoint(camera).x,PickPoint(camera).y);
		}
		
	/*	if(IsKeyPressed(KEY_X)){
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
		}	*/
		
			
/*		if(type == GRASS){
			CalculateRange(Map,&tiles,x,y,3,type);
			LimitRange(Map,&tiles,FERTELIZED);
		}else{
			CalculateRange(Map,&tiles,x,y,6,type);
			FactoryRanges(Map,&tiles);	
			LimitRange(Map,&tiles,BARREN);
		}*/
//		AffectedTile* temp = tiles;	
		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || Do){
			if(money>=cost && tiles){
				PlaySound(sounds[selected]);
				Addframe(Map,&animations,&tiles,false);
				money += AffectMap(Map,&tiles);
				money -= cost;
				Do=false;
			}
		}
		if(money<25){
			talk = 28;
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
		int gain = 0;
		{
			AffectedTile* temp = tiles;
			while(temp){
				gain++;
				temp = temp->Next;
			}
		//	printf("%d\n",cost);
			switch(selected){
				case 0:
					gain = 0;
					gain -= 25;
					break;
				case 1:
					gain *= 5;
					gain -=100;
					break;
				case 2:
					gain *= 20;
					gain -= 200;
					break;
				case 3:
					gain *= 20;
					gain -= 200;
					break;
				case 4:
					gain = 0;
					gain -=400;
					break;				
			}
		}
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
//		talk = 3;
		if(talk <27){
			Tutorial(&talk,&talkcounter,mommy);
		}
		if(talk == 28){
			
			float offset = (float)overcounter/5-4;
			if(overcounter >=25){
				offset = 0;
			}else if(overcounter < 25){
				overcounter++;
				offset = -offset *offset +1;
			}
			talkcounter++;
			DrawRectangle(100,100-offset*30,600,150,BROWN);
			DrawRectangleLinesEx((Rectangle){100,100-offset*30,600,150},3,DARKBROWN);
			DrawRectangle(105,105-offset*30,128,128,LIME);		
			DrawTexture(dommy,105,105-offset*30,WHITE);
			DrawRectangleLinesEx((Rectangle){105,105-offset*30,128,128},3,DARKGREEN);
			DrawText(" Would you look at that ! it appears ",240,110-offset*30,19,BLACK);
			DrawText("YOU LOST",240+MeasureText(" Would you look at that ! it appears ",19),110-offset*30,19,RED);
			DrawText(" Say goodbye to the sun, your job is done. . . ",240,130-offset*30,19,BLACK);
			DrawText(" and so are you <3 ",240,150-offset*30,19,RED);
			if(Button("Restart",330,190-offset*30,100,40,19)){
				talk = 26;
			}
			if(Button("Menu",470,190-offset*30,100,40,19)){
				
			}
		}
		if(talk == 4 || talk == 5){
			ButtonDance(300+50*selected,350,40,40,power[0],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 5){
				Do = true;
			}
		}else if(talk == 6 || talk == 7){
			selected = 1;
			ButtonDance(300+50*selected,350,40,40,power[1],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 7){
				Do = true;
			}
		}else if(talk == 8 || talk == 9){
			selected = 2;
			ButtonDance(300+50*selected,350,40,40,power[2],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 9){
				Do = true;
			}
		}else if(talk == 10 || talk == 11){
			selected = 3;
			ButtonDance(300+50*selected,350,40,40,power[3],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 11){
				Do = true;
			}
		}else if(talk == 12){
			Vector2 target = (Vector2){348,77};
			camera.target.x -= (camera.target.x-target.x)/50;
			camera.target.y -= (camera.target.y-target.y)/50;
		}else if(talk == 13 || talk == 14){
			camera.target = (Vector2){348,77};
			selected = 4;
			ButtonDance(300+50*selected,350,40,40,power[4],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 14){
				Do = true;
			}
		}else if(talk == 15){
			Vector2 target = (Vector2){41,-104};
			camera.target.x -= (camera.target.x-target.x)/50;
			camera.target.y -= (camera.target.y-target.y)/50;
		}else if(talk == 16 || talk == 17 || talk == 20|| talk == 21){
			camera.target = (Vector2){41,-104};
			selected = 0;
			ButtonDance(300+50*selected,350,40,40,power[0],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& (talk == 17|| talk == 21)){
				Do = true;
			}
		}else if(talk == 18 || talk == 19){
			selected = 4;
			ButtonDance(300+50*selected,350,40,40,power[4],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 19 ){
				Do = true;
			}
		}else if(talk == 22){
			Vector2 target = (Vector2){27,410};
			camera.target.x -= (camera.target.x-target.x)/50;
			camera.target.y -= (camera.target.y-target.y)/50;
		}else if(talk == 23 || talk == 24){
			camera.target = (Vector2){27,410};
			selected = 4;
			ButtonDance(300+50*selected,350,40,40,power[4],talkcounter);
			if(IsKeyPressed(KEY_ENTER)&& talk == 24 ){
				Do = true;
			}
		}else if(talk == 27){		
			DrawRectangle(50,0,50,50,WHITE);
			DrawText(TextFormat("%d",money),53,0,25,BLACK);
			Color smth;
			if(gain<=0){
				smth = RED;
			}else{
				smth = GREEN;
			}
			DrawText(TextFormat("%d",gain),53,25,25,smth);
			ButtonTexture(0,0,50,50,power[selected]);
				for(int i =0;i<5;i++){
				if(ButtonTexture(300+i*50,350,40,40,power[i]))
					selected = i;
					DrawText(TextFormat("%d",i+1),303+i*50,353,15,BLACK);	
				}
		}
		
    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

