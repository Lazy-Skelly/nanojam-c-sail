#include "Utils.h"
#include "Tiles.h"
#include "Camera.h"
#include "Renderer.h"
#include "UI.h"
#include "Menu.h"
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
	SetTraceLogLevel(LOG_NONE);
    InitWindow(WIDTH,HEIGHT,"DEFOREST");
   // ToggleBorderlessWindowed();
    InitAudioDevice();   
    SetTargetFPS(60);
	
	ReinitializeMap(Map);
	AffectedTile* tiles = NULL;
	
	
	
//	printf("halo");
	int x,y;
	x=50;
	y=20;
	Animated* animations = NULL;
	
	Sound ost = LoadSound("sprites/Light on a Window.mp3");
	Sound over = LoadSound("sprites/Game Over.mp3");
	Sound sea = LoadSound("sprites/Waves.mp3");
	Sound seagulls = LoadSound("sprites/Seagulls.mp3");
	Sound piano = LoadSound("sprites/Serenity.mp3");
	Sound sounds[5] ;
	Sound nah = LoadSoundFromWave(LoadWave("sprites/synth.wav"));
	Sound water = LoadSoundFromWave(LoadWave("sprites/water.wav"));
	sounds[0] = LoadSoundFromWave(LoadWave("sprites/magic.wav"));
	sounds[1] = LoadSoundFromWave(LoadWave("sprites/grass.wav"));
	sounds[2] = LoadSoundFromWave(LoadWave("sprites/forest.wav"));
	sounds[3] = LoadSoundFromWave(LoadWave("sprites/forest.wav"));
	sounds[4] = LoadSoundFromWave(LoadWave("sprites/crash.wav"));
	
	Texture2D texture = LoadTexture("sprites/spritesheet.png");
	Texture2D progress = LoadTexture("sprites/Progress.png");
	Texture2D menu = LoadTexture("sprites/DEFOREST.png");
	Texture2D mommy = LoadTexture("sprites/dommymommy.png");
	Texture2D dommy = LoadTexture("sprites/Dommymommydissapointedinyou.png");
	Texture2D recycle = LoadTexture("sprites/money.png");
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

	Texture2D title = LoadTexture("sprites/DEFOREST.png");
	Texture2D logo = LoadTexture("sprites/logo.png");
	
	Rectangle source= {0,0,32,32};
	Image image = LoadImage("sprites/maptutorialp.png");
	Color* color = LoadImageColors(image);
	
	Shader shader = LoadShader(0,"sprites/shader.fs");
	int PercentageUniform = GetShaderLocation(shader,"percentage");

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
	int strength =00;
	int talk = 0;
	int talkcounter = 0;
	int choice = -2;
	int overcounter =0;
	bool Do = false;
	int around = -50;
	SetMasterVolume(0.4);
	SetExitKey(KEY_NULL);
	int menucounter = -1;
	bool NoWin = false;
    while (!WindowShouldClose()) {
    	if(choice == -2){
    		choice = LogoScreen(logo,sea,seagulls);
    		continue;
    	}else if(choice == -1){
    		if(!IsSoundPlaying(piano))
    			PlaySound(piano);
			if(IsSoundPlaying(ost))
				StopSound(ost);		
			
			choice  = StartMenuBefore(title,400,800,&menucounter);
			around = -50;
			continue;
		}
		if(IsSoundPlaying(piano))
    		StopSound(piano);
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
		
		float percentage = Percentage(Map);
		if(percentage >0.90 && !NoWin && !builds){
			talk = 29;
		}	
	
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(DARKGRAY);
        Vector2 stuff;
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
				cost = 350;
				break;
			case 3:
				CalculateRange(Map,&tiles,stuff.x,stuff.y,4+strength,JUNGLE);
				LimitRange(Map,&tiles,GRASS);
				cost = 350;
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
 			NoWin = false;
 			Image image = LoadImage(TextFormat("sprites/map%d.png",choice));
			Color* color = LoadImageColors(image);	
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
			money = 300;
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
		
/*		if(IsKeyPressed(KEY_X)){
			printf("%f,%f\n",camera.target.x,camera.target.y);
			printf("mouse %f,%f\n",PickPoint(camera).x,PickPoint(camera).y);
		}*/

		if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || Do){
			if(10>rand()%100){
				int ran = rand()%14;
				switch(ran){
					case 0:
						SetWindowTitle("Why you looking here?");
						break;
					case 1:
						SetWindowTitle("Dont you have a thing to do?");
						break;
					case 2:
						SetWindowTitle("Well hello there!");
						break;
					case 3:
						SetWindowTitle("NEWS: gamer not focusing on game");
						break;
					case 4:
						SetWindowTitle("vote for DEFOREST");
						break;
					case 5:
						SetWindowTitle("DEFOREST");
						break;
					case 6:
						SetWindowTitle("made by tired lich, snake & faycal");
						break;
					case 7:
						SetWindowTitle("made out of pure potato and salt");
						break;
					case 8:
						SetWindowTitle("big boot, big booty");
						break;
					case 9:
						SetWindowTitle("the house always wins");
						break;
					case 10:
						SetWindowTitle("how much your spine can take");
						break;	
					case 11:
						SetWindowTitle("space 12!!! OHOHOHOHOOOO");
						break;
					case 12:
						SetWindowTitle("the game is down there");
						break;	
					case 13:
						SetWindowTitle("spread hate");
						break;				
				}
			}
			if(money>=cost && tiles){
				PlaySound(sounds[selected]);
				Addframe(Map,&animations,&tiles,false);
				money += AffectMap(Map,&tiles);
				money -= cost;
				Do=false;
			}else if(money<cost && tiles){
				PlaySound(nah);
			}
		}
		if(money<25){
			talk = 28;
		}
		
		int gain = 0;
		{
			AffectedTile* temp = tiles;
			while(temp){
				gain++;
				temp = temp->Next;
			}
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
					gain -= 350;
					break;
				case 3:
					gain *= 20;
					gain -= 350;
					break;
				case 4:
					gain = 0;
					gain -=400;
					break;				
			}
		}
		Draw(Map,texture,&animations,&tiles,&builds);
		
		while(tiles){
			AffectedTile* temp = tiles->Next;
			free(tiles);
			tiles = temp;
		}
		EndMode2D();
		
		if(talk <27){
			Tutorial(&talk,&talkcounter,mommy,dommy);
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
				//around = -50;
				choice = -1;
				talk = 26;
				ReinitializeMap(Map);
				StopSound(over);
				PlaySound(piano);
				menucounter=-1;
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
			if(IsKeyPressed(KEY_ESCAPE)){
				overcounter=0;
				talk = 30;
			}		
			DrawRectangle(50,0,10+MeasureText(TextFormat("%d",money),25),52,(Color){153,229,80,255});
			DrawRectangleLines(50,0,10+MeasureText(TextFormat("%d",money),25),52,GOLD);
			DrawText(TextFormat("%d",money),55,3,25,BLACK);

		/*	DrawRectangle(50,0,10+MeasureText(TextFormat("%d",money),25),52,LIGHTGRAY);
			DrawRectangleLines(50,0,10+MeasureText(TextFormat("%d",money),25),52,GOLD);
			DrawText(TextFormat("%d",money),55,3,25,BLACK);*/
			Color smth;
			if(gain<=0){
				smth = RED;
			}else{
				smth = GREEN;
			}
			BeginShaderMode(shader);
		//	percentage = 0.6;
			SetShaderValue(shader,PercentageUniform,&percentage,0);
			DrawTexture(progress,600,0,WHITE);
			EndShaderMode();
			DrawText(TextFormat("%d",gain),53,28,25,smth);
			ButtonTexture(0,0,52,52,power[selected]);
				for(int i =0;i<5;i++){
				if(ButtonTexture(275+i*55,350,50,50,power[i]))
					selected = i;
					DrawText(TextFormat("%d",i+1),278+i*55,353,15,BLACK);	
				}
		}else if(talk == 29){
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
			DrawTexture(mommy,105,105-offset*30,WHITE);
			DrawRectangleLinesEx((Rectangle){105,105-offset*30,128,128},3,DARKGREEN);
			DrawText(" Would you look at that ! it appears ",240,110-offset*30,19,BLACK);
			DrawText("YOU DID IT",240+MeasureText(" Would you look at that ! it appears ",19),110-offset*30,19,GREEN);
			DrawText(" I didnt expect you to be actually competent",240,130-offset*30,19,BLACK);
			DrawText(" I would say you deserve to live another day <3 ",240,150-offset*30,19,GREEN);
			if(Button("Continue",280,190-offset*30,100,40,19)){
				talk = 27;
				NoWin = true;
			}
			if(Button("NEXT",400,190-offset*30,100,40,19)){
				choice++;
				choice = choice%3;
				NoWin = true;
				talk = 26;
			}
			if(Button("Menu",520,190-offset*30,100,40,19)){
				//around = -50;
				NoWin = false;
				choice = -1;
				talk = 26;
				ReinitializeMap(Map);
				StopSound(over);
				PlaySound(piano);
				menucounter=-1;
			}
		}else if(talk == 30){
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
			DrawTexture(mommy,105,105-offset*30,WHITE);
			DrawRectangleLinesEx((Rectangle){105,105-offset*30,128,128},3,DARKGREEN);
			DrawText(" Pausing , what a disgrace ",240,110-offset*30,19,BLACK);
		//	DrawText("YOU DID IT",240+MeasureText(" Would you look at that ! it appears ",19),110-offset*30,19,GREEN);
			DrawText(" already quitting or maybe restarting , ",240,130-offset*30,19,BLACK);
			DrawText(" pathetic ",240+MeasureText(" already quitting or maybe you restart, ",19),130-offset*30,19,RED);
			DrawText(" Well never had hope in you anyway <3",240,150-offset*30,19,GREEN);
			if(Button("Continue",280,190-offset*30,100,40,19)||IsKeyPressed(KEY_ESCAPE)){
				talk = 27;
			}
			if(Button("Restart",400,190-offset*30,100,40,19)){
				talk = 26;
				NoWin = true;
			}
			if(Button("Menu",520,190-offset*30,100,40,19)){
			//	around = -50;
				NoWin = false;
				choice = -1;
				talk = 26;
				ReinitializeMap(Map);
				StopSound(over);
				PlaySound(piano);
				menucounter=-1;
			}
		}
		
		if(around<180 && around>=0){
			around++;
        	DrawRectanglePro((Rectangle){0-around*4,0,800,200},(Vector2){0,0},-around,BLACK);
        	DrawRectanglePro((Rectangle){800+around*4,400,800,200},(Vector2){0,0},180-around,BLACK);
		}else if(around<-20){
			StillMenu(title,400,800);
			around++;
        	float smth = (float)(-20-around)/30;
        	int offsetx = -800*smth;
        	//printf("%d\n",offsetx);
        	DrawRectanglePro((Rectangle){offsetx,0,800,200},(Vector2){0,0},0,BLACK);
        	DrawRectanglePro((Rectangle){0-offsetx,200,800,200},(Vector2){0,0},0,BLACK);
		}else if(around>=-20 && around<0){
			around++;
        	DrawRectanglePro((Rectangle){0,0,800,200},(Vector2){0,0},0,BLACK);
        	DrawRectanglePro((Rectangle){800,400,800,200},(Vector2){0,0},180,BLACK);
		}
		
    	EndDrawing();
	}
	
	
CloseWindow();
return 0;
}

