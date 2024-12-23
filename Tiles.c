#include "Tiles.h"

void ReinitializeMap(Tile Map[WORLDSIZE][WORLDSIZE]){
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			Map[i][j].Type = BARREN;
		}
	}
} 

void AffectMap(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles){
	AffectedTile* tile = *tiles;
	while(tile){
		Map[tile->x][tile->y].Type = tile->Type;
		
		AffectedTile* temp = tile->Next;
		free(tile);
		tile = temp;
	}
	*tiles=NULL;
}

void AddTile(AffectedTile** tiles ,int x, int y, int type){
	AffectedTile* temp = NEW(AffectedTile,1);
	temp->x = x;
	temp->y = y;
	temp->Type = type;
	temp->Next = *tiles;
	*tiles = temp;
}

bool SearchList(AffectedTile** tiles,int x, int y){
	AffectedTile* tile = *tiles;
	while(tile){
		if(tile->x == x && tile->y == y){
			return true;
		}
		tile = tile->Next;
	}
	return false;
}

void CalculateRange(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int x, int y, int Power, int type){
	if(x>=0 && x <WORLDSIZE && y>=0 && y<WORLDSIZE && Power !=0){
		if(!SearchList(tiles,x,y))
			AddTile(tiles,x,y,type);
	
		if(Map[x-1][y].Type != CITY && Map[x-1][y].Type != FACTORY)
			CalculateRange(Map,tiles,x-1,y,Power-1,type);
		
		if(Map[x+1][y].Type != CITY && Map[x+1][y].Type != FACTORY)
			CalculateRange(Map,tiles,x+1,y,Power-1,type);
		
		if(Map[x][y-1].Type != CITY && Map[x][y-1].Type != FACTORY)
			CalculateRange(Map,tiles,x,y-1,Power-1,type);
		
		if(Map[x][y+1].Type != CITY && Map[x][y+1].Type != FACTORY)
			CalculateRange(Map,tiles,x,y+1,Power-1,type);				
	}
}

void CalculateRangeEarth(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int x, int y, int Power, int type){
	if(x>=0 && x <WORLDSIZE && y>=0 && y<WORLDSIZE && Power !=0){
		if(!SearchList(tiles,x,y))
			AddTile(tiles,x,y,type);
	
		CalculateRangeEarth(Map,tiles,x-1,y,Power-1,type);
		CalculateRangeEarth(Map,tiles,x+1,y,Power-1,type);
		CalculateRangeEarth(Map,tiles,x,y-1,Power-1,type);		
		CalculateRangeEarth(Map,tiles,x,y+1,Power-1,type);				
	}
}

void DeleteTile(AffectedTile** tiles, int x, int y){
	if(*tiles == NULL)
		return;
	
	if((*tiles)->x == x && (*tiles)->y == y){
		AffectedTile* temp = *tiles;
		*tiles = (*tiles)->Next;
		free(temp);
		return;
	}
	AffectedTile* tile = *tiles;
	AffectedTile* before = tile;
	tile = tile->Next;
	while(tile){
		if(tile->x == x && tile->y == y){
			before->Next = tile->Next;
			free(tile);
			return;
		}
		before = tile;
		tile = tile->Next;
	}	
}

void FactoryRanges(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles){
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == FACTORY){
				AffectedTile* factory = NULL;
				CalculateRange(Map,&factory,i,j,FACTORYINFLUENCE,BARREN);
				while(factory){
					DeleteTile(tiles,factory->x,factory->y);
					AffectedTile* temp = factory->Next;
					free(factory);
					factory = temp;
				}
			}
		}
	}
}

void LimitRange(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int type){
	AffectedTile* temp = *tiles;
	while(temp){
		if(Map[temp->x][temp->y].Type != type){
			int x, y;
			x = temp->x;
			y = temp->y;
			temp = temp->Next;
			DeleteTile(tiles,x,y);
		}else{
			temp = temp->Next;	
		}
	}
}

void LimitRange2(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int type, int type2){
	AffectedTile* temp = *tiles;
	while(temp){
		if(Map[temp->x][temp->y].Type == type || Map[temp->x][temp->y].Type == type2){
			temp = temp->Next;	
		}else{
			int x, y;
			x = temp->x;
			y = temp->y;
			temp = temp->Next;
			DeleteTile(tiles,x,y);
		}
	}
}

bool WaterCheck(Tile Map[WORLDSIZE][WORLDSIZE],AffectedTile** tiles){
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == CONWATER){
				return false;
			}
		}
	}
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == BADWATER){
				AddTile(tiles,i,j,WATER);
			}
		}
	}
	return true;
}

void WaterInfluence(Tile Map[WORLDSIZE][WORLDSIZE],AffectedTile** tiles){
	
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == WATER){
				CalculateRange(Map,tiles,i,j,3,GRASS);
				LimitRange2(Map,tiles,BARREN,FERTELIZED);
			}
		}
	}
}

void EarthQuake(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** tiles, int x, int y){
	CalculateRangeEarth(Map,tiles,x,y,EARTHQUAKE,RUIN);
 	LimitRange2(Map,tiles,FACTORY,CONWATER);
}

bool bigcheck(Tile Map[WORLDSIZE][WORLDSIZE], int x, int y){
	return Map[x][y].Type == GRASS || Map[x][y].Type == WATER || Map[x][y].Type == FOREST || Map[x][y].Type == JUNGLE || Map[x][y].Type == RUIN || Map[x][y].Type == ECORUIN;
}

void CheckRuins(Tile Map[WORLDSIZE][WORLDSIZE], AffectedTile** ruin){
	AffectedTile* tiles = NULL;
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == RUIN){
				AddTile(&tiles,i,j,RUIN);
			}
		}
	}
	while(tiles){
		if(bigcheck(Map,tiles->x-1,tiles->y)&&bigcheck(Map,tiles->x+1,tiles->y)&&bigcheck(Map,tiles->x,tiles->y-1)&&bigcheck(Map,tiles->x,tiles->y+1)){
			AddTile(ruin,tiles->x,tiles->y,ECORUIN);		
		}
		AffectedTile* temp = tiles;
		tiles = tiles->Next;
		free(temp);
	}
}
//testing 

void DrawMap(Tile Map[WORLDSIZE][WORLDSIZE]){
	for(int i=0;i<WORLDSIZE;i++){
		for(int j=0;j<WORLDSIZE;j++){
			if(Map[i][j].Type == FACTORY){
				DrawRectangle(i*5+20,j*5+20,5,5,BLACK);
			}else if(Map[i][j].Type == BARREN){	
				DrawRectangle(i*5+20,j*5+20,5,5,RED);
			}else if(Map[i][j].Type == WATER){	
				DrawRectangle(i*5+20,j*5+20,5,5,BLUE);
			}else if(Map[i][j].Type == FERTELIZED){	
				DrawRectangle(i*5+20,j*5+20,5,5,BROWN);
			}else if(Map[i][j].Type == GRASS){	
				DrawRectangle(i*5+20,j*5+20,5,5,GREEN);
			}else if(Map[i][j].Type == FOREST){	
				DrawRectangle(i*5+20,j*5+20,5,5,DARKGREEN);
			}else if(Map[i][j].Type == JUNGLE){	
				DrawRectangle(i*5+20,j*5+20,5,5,LIME);
			}else if(Map[i][j].Type == CITY){	
				DrawRectangle(i*5+20,j*5+20,5,5,DARKGRAY);
			}else if(Map[i][j].Type == BADWATER){	
				DrawRectangle(i*5+20,j*5+20,5,5,MAROON);
			}else if(Map[i][j].Type == ECORUIN){	
				DrawRectangle(i*5+20,j*5+20,5,5,PURPLE);
			}
		}
	}
}
