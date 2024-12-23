#include "Utils.h"
#include "Renderer.h"

Rectangle BARRENTEXTURE = {0*32,0*32,32,32};
Rectangle FERTILETEXTURE = {9*32,1*32,32,32};
Rectangle GRASSTEXTURE = {0,2*32,32,32};
Rectangle FORESTTEXTURE = {9*32,2*32,32,32};
Rectangle JUNGLETEXTURE = {3*32,3*32,32,32};
Rectangle CITYTEXTURE = {3*32,6*32,32,32};
Rectangle FACTORYTEXTURE = {3*32,6*32,32,32};
Rectangle CONWATERTEXTURE = {3*32,6*32,32,32};
Rectangle WATERTEXTURE = {0*32,10*32,32,32};
Rectangle RUINTEXTURE = {5*32,6*32,32,32};
Rectangle BADWATERTEXTURE = {0,8*32,32,32};
Rectangle ECORUINTEXTURE = {6*32,5*32,32,32};

void Draw(Tile Map[WORLDSIZE][WORLDSIZE], Texture2D texture, Animated** list, AffectedTile** highlight, Building** builds){
	for(int i = 0; i< WORLDSIZE;i++){
		for(int j =0;j < WORLDSIZE;j++){
			Animated* animation = GetAnimated(list,i,j);
			Color color;
			if(SearchList(highlight,i,j)){
				color = ColorAlpha(LIGHTGRAY,1);
			}else{
				color = WHITE;
			}
			if(animation){
				int type = animation->frame > 0 ? Map[i][j].Type : animation->type;
				float offset = MAX((float)animation->frame,0.0);
				offset = -(offset/15-1)*(offset/15-1)+1;
				offset *=-16;
				//printf("%d\n",offset);
				animation->frame++;
				
				
				if(type == FACTORY){
					DrawTexturePro(texture,FACTORYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == BARREN){	
					DrawTexturePro(texture,BARRENTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == WATER){
					DrawTexturePro(texture,WATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);	
				}else if(type == FERTELIZED){
					DrawTexturePro(texture,FERTILETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);	
				}else if(type == GRASS){
					DrawTexturePro(texture,GRASSTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);	
				}else if(type == FOREST){	
					DrawTexturePro(texture,FORESTTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == JUNGLE){	
					DrawTexturePro(texture,JUNGLETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == CITY){	
					DrawTexturePro(texture,CITYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == BADWATER){	
					DrawTexturePro(texture,BADWATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == ECORUIN){	
					DrawTexturePro(texture,ECORUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == RUIN){	
					DrawTexturePro(texture,RUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}else if(type == CONWATER){	
					DrawTexturePro(texture,CONWATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8)+offset,32,32},(Vector2){0,0},0,color);
				}		
				if(animation->frame <30){
					AddAnimated(list,animation->x,animation->y,animation->type,animation->frame);
				}
				free(animation);
					
			}else{
				if(Map[i][j].Type == FACTORY){
					DrawTexturePro(texture,FACTORYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == BARREN){	
					DrawTexturePro(texture,BARRENTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == WATER){
					DrawTexturePro(texture,WATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);	
				}else if(Map[i][j].Type == FERTELIZED){
					DrawTexturePro(texture,FERTILETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);	
				}else if(Map[i][j].Type == GRASS){
					DrawTexturePro(texture,GRASSTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);	
				}else if(Map[i][j].Type == FOREST){	
					DrawTexturePro(texture,FORESTTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == JUNGLE){	
					DrawTexturePro(texture,JUNGLETEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == CITY){	
					DrawTexturePro(texture,CITYTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == BADWATER){	
					DrawTexturePro(texture,BADWATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == ECORUIN){	
					DrawTexturePro(texture,ECORUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == RUIN){	
					DrawTexturePro(texture,RUINTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}else if(Map[i][j].Type == CONWATER){	
					DrawTexturePro(texture,CONWATERTEXTURE,(Rectangle){400-(i*16)+(j*16),0+j*8+(i*8),32,32},(Vector2){0,0},0,color);
				}
			}
			DrawSingle(Map,builds,i,j);
		}
	}
}

void AddAnimated(Animated** list, int x, int y, int type, int frame){
	Animated* temp = NEW(Animated,1);
	temp->x = x;
	temp->y = y;
	temp->type = type;
	temp->frame = frame;
	temp->next = *list;
	*list = temp;
}

Animated* GetAnimated(Animated** list, int x, int y){
	if(*list == NULL)
		return NULL;
	
	if((*list)->x == x && (*list)->y == y){
		Animated* temp = *list;
		*list = (*list)->next;
		return temp;
	}
	Animated* tile = *list;
	Animated* before = tile;
	tile = tile->next;
	while(tile){
		if(tile->x == x && tile->y == y){
			before->next = tile->next;
			return tile;
		}
		before = tile;
		tile = tile->next;
	}
}

void Addframe(Tile Map[WORLDSIZE][WORLDSIZE],Animated** list, AffectedTile** tiles, bool world){
	AffectedTile* temp = *tiles;
	while(temp){
		if(world){
			AddAnimated(list,temp->x,temp->y,Map[temp->x][temp->y].Type,-temp->y);
		}else{	
			AddAnimated(list,temp->x,temp->y,Map[temp->x][temp->y].Type,0);
		}
		temp = temp->Next;
	}
}

void DrawSingle(Tile Map[WORLDSIZE][WORLDSIZE],Building** builds,int x, int y){
	if(*builds){
		Building* temp = *builds;
		while(temp){
		if(temp->type == FACTORY){
			if(x != temp->x+1 || y != temp->y+1){
				temp = temp->next;
				continue;
			}
		}else if(x != temp->x || y != temp->y){
			temp = temp->next;
			continue;
		}
		//printf("hallo");
			if(Map[temp->x][temp->y].Type == RUIN || Map[temp->x][temp->y].Type == ECORUIN){
				int x = temp->x;
				int y = temp->y;
				temp = temp->next;
				RemoveBuild(builds,x,y);
			}else{
				Texture texture = temp->texture;
			//	printf("%d,%d,%d%,d\n",texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height);
				if(temp->type == CONWATER){
					Rectangle source = {texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16),0+temp->y*8+(temp->x*8)-8,32,32};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
					temp->frame++;
					temp->frame = temp->frame%temp->size;
				}else if(temp->type == FACTORY){
					Rectangle source = {texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16)-8,0+temp->y*8+(temp->x*8)-6,48,48};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
					temp->frame++;
					temp->frame = temp->frame%temp->size;
				}else{
					Rectangle source = (Rectangle){texture.width/4 * temp->size,0,32,32};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16),0+temp->y*8+(temp->x*8)-8,32,32};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
				}
			}
				return;
		}
	}
}

void DrawBuilding(Tile Map[WORLDSIZE][WORLDSIZE], Building** builds){
	if(*builds){
		Building* temp = *builds;
		//printf("hallo");
		while(temp){
			if(Map[temp->x][temp->y].Type == RUIN || Map[temp->x][temp->y].Type == ECORUIN){
				int x = temp->x;
				int y = temp->y;
				temp = temp->next;
				RemoveBuild(builds,x,y);
			}else{
				Texture texture = temp->texture;
			//	printf("%d,%d,%d%,d\n",texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height);
				if(temp->type == CONWATER){
					Rectangle source = {texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16),0+temp->y*8+(temp->x*8)-8,32,32};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
					temp->frame++;
					temp->frame = temp->frame%temp->size;
				}else if(temp->type == FACTORY){
					Rectangle source = {texture.width/temp->size * temp->frame,0,texture.width/temp->size,texture.height};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16)-8,0+temp->y*8+(temp->x*8)-6,48,48};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
					temp->frame++;
					temp->frame = temp->frame%temp->size;
				}else{
					Rectangle source = (Rectangle){texture.width/4 * temp->size,0,32,32};
					Rectangle destination = {400-(temp->x*16)+(temp->y*16),0+temp->y*8+(temp->x*8)-8,32,32};
					DrawTexturePro(texture,source,destination,(Vector2){0,0},0,WHITE);
				}
				temp = temp->next;
			}
		}
	}
}

void AddBuilding(Building** builds,int type,int x, int y, int frame, int size, Texture2D texture){
	Building* temp = NEW(Building,1);
	temp->x = x;
	temp->y = y;
	temp->frame = frame;
	temp->type = type;
	temp->size = size;
	temp->texture = texture;
	temp->next = *builds;
	*builds = temp;
}

void RemoveBuild(Building** list, int x, int y){
	if(*list == NULL)
		return;
	
	if((*list)->x == x && (*list)->y == y){
		Building* temp = *list;
		*list = (*list)->next;
		free(temp);
		return;
	}
	Building* tile = *list;
	Building* before = tile;
	tile = tile->next;
	while(tile){
		if(tile->x == x && tile->y == y){
			before->next = tile->next;
			free(tile);
			return;
		}
		before = tile;
		tile = tile->next;
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
