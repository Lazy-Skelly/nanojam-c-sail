#include "Utils.h"
#include "Renderer.h"

Rectangle BARRENTEXTURE = {0*32,0*32,32,32};
Rectangle FERTILETEXTURE = {9*32,1*32,32,32};
Rectangle GRASSTEXTURE = {0,2*32,32,32};
Rectangle FORESTTEXTURE = {9*32,2*32,32,32};
Rectangle JUNGLETEXTURE = {0,2*32,32,32};
Rectangle CITYTEXTURE = {3*32,6*32,32,32};
Rectangle FACTORYTEXTURE = {3*32,6*32,32,32};
Rectangle WATERTEXTURE = {0*32,10*32,32,32};
Rectangle RUINTEXTURE = {5*32,6*32,32,32};
Rectangle BADWATERTEXTURE = {0,8*32,32,32};
Rectangle ECORUINTEXTURE = {6*32,5*32,32,32};

void Draw(Tile Map[WORLDSIZE][WORLDSIZE], Texture2D texture){
	for(int i = 0; i< WORLDSIZE;i++){
		for(int j =0;j < WORLDSIZE;j++){
			if(Map[i][j].Type == FACTORY){
				DrawTexturePro(texture,FACTORYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == BARREN){	
				DrawTexturePro(texture,BARRENTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == WATER){
				DrawTexturePro(texture,WATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);	
			}else if(Map[i][j].Type == FERTELIZED){
				DrawTexturePro(texture,FERTILETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);	
			}else if(Map[i][j].Type == GRASS){
				DrawTexturePro(texture,GRASSTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);	
			}else if(Map[i][j].Type == FOREST){	
				DrawTexturePro(texture,FORESTTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == JUNGLE){	
				DrawTexturePro(texture,JUNGLETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == CITY){	
				DrawTexturePro(texture,CITYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == BADWATER){	
				DrawTexturePro(texture,BADWATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == ECORUIN){	
				DrawTexturePro(texture,ECORUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}else if(Map[i][j].Type == RUIN){	
				DrawTexturePro(texture,RUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,WHITE);
			}
			
			
			
		}
	}
}

Vector2 PickPoint(Camera2D camera){
	Vector2 mouse = GetMousePosition();
	mouse = Vector2Add(mouse,camera.target);
//	CheckCollisionPointTriangle();
	int i = (2*mouse.y+400-mouse.x)/32;
	int j = (2*mouse.y-400+mouse.x)/32;
	return (Vector2){i,j-1};	
}
