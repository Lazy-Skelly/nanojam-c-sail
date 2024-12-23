#include "UI.h"

bool Button(const char* text, int x, int y, int width, int height, int font){
	DrawRectangle(x,y,width,height,(Color){128,239,128,255});
	DrawRectangleLinesEx((Rectangle){x,y,width,height},3,GREEN);
	int size = MeasureText(text,font);
	int offsetx = (width - size)/2;
	int offsety = (height - font)+3;
	DrawText(text,x+offsetx,y+offsety,font,SKYBLUE);
	
	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		return CheckCollisionPointRec(GetMousePosition(),(Rectangle){x,y,width,height});
	return false;	
}

bool ButtonTexture(int x, int y, int width, int height, Texture2D texture){
	DrawRectangle(x,y,width,height,(Color){128,239,128,255});
	DrawRectangleLinesEx((Rectangle){x,y,width,height},3,GREEN);
	DrawTexturePro(texture,(Rectangle){0,0,texture.width,texture.width},(Rectangle){x+3,y+3,width-6,height-6},(Vector2){0,0},0,WHITE);

	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		return CheckCollisionPointRec(GetMousePosition(),(Rectangle){x,y,width,height});
}
