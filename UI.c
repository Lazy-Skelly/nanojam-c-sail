#include "UI.h"

bool Button(const char* text, int x, int y, int width, int height, int font){
	DrawRectangle(x,y,width,height,SKYBLUE);
	DrawRectangleLinesEx((Rectangle){x,y,width,height},3,BLUE);
	int size = MeasureText(text,font);
	int offsetx = (width - size)/2;
//	int offsety = (height - font)+3;
	DrawText(text,x+offsetx,y+10,font,BLACK);
	
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

bool ButtonDance(int x, int y, int width, int height, Texture2D texture, int counter){
	int offset = sin((float)counter/10)*10;
	Color color;
	if(counter%30 <15){
		color = GREEN;
	}else{
		color = RED;
	}
	DrawRectangle(x,y+offset,width,height,(Color){128,239,128,255});
	DrawRectangleLinesEx((Rectangle){x,y+offset,width,height},3,color);
	DrawTexturePro(texture,(Rectangle){0,0,texture.width,texture.width},(Rectangle){x+3,y+3+offset,width-6,height-6},(Vector2){0,0},0,WHITE);
	if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		return CheckCollisionPointRec(GetMousePosition(),(Rectangle){x,y,width,height});
}

void DancingText(const char* text,int counter,int x, int y){
	//printf("%d\n",TextLength(text));	
	int offset = 0;
	int old;
	for(int i =0; i< TextLength(text);i++){
		char* temp = TextSubtext(text,i,1);
		old = MeasureText(temp,19);
		if(i>0){
			offset += old+1;
		}
		//printf("%d ",old);
		DrawText(&temp[0],x+offset,y+sin((float)counter/10 + 1.5+i*0.3)*8,19,RED);
		free(temp);
	}
}

bool Tutorial(int* talk, int* talkcounter, Texture2D mommy){
		if(*talk == 26)
			return true;
		if(*talk <4){
			DrawRectangle(0,250,800,150,BROWN);
			DrawRectangleLinesEx((Rectangle){0,250,800,150},3,DARKBROWN);
			DrawRectangle(141,262,650,120,LIGHTGRAY);
		}else{
			DrawRectangle(0,0,800,150,BROWN);
			DrawRectangleLinesEx((Rectangle){0,0,800,150},3,DARKBROWN);
			DrawRectangle(141,18,650,120,LIGHTGRAY);
		}
	//	DrawRectangleLinesEx((Rectangle){0,250,800,150},3,DARKBROWN);
		switch(*talk){
			case 0:
				DrawText(" Well Well Well, you humans have overstepped your boundaries for the",138,268,19,BLACK);
				DrawText(" last time,Countless trees and animals die to your greed and expansions!",138,288,19,BLACK);
				DrawText(" I won't be standing IDLY you HEAR >:c ?!",138,328,19,BLACK);
				DrawText(" Press enter to continue",538,358,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 1;
				}
				break;
			case 1:
				DrawText(" Hey, You There,From now on . . .",138,268,19,BLACK);
				(*talkcounter)++;
				if(*talkcounter == 180){
					*talk =2;
				}
				break;
			case 2:
				DrawText(" YOU ! ! ! from now on will be the \"nature architect\". your job? simple . . .",138,268,19,BLACK);
				DrawText(" you make grass grow and trees thrive remove any nuasance from ",138,288,19,BLACK);
				DrawText(" factories to cities you find, your job is done once they are ALL GONE",138,308,19,BLACK);
				DrawText(" got that ? Perfect!",138,328,19,BLACK);
				DrawText(" Press enter to continue",538,358,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 3;
				}
				break;
			case 3:
				DrawText(" In order to perform your work you got nature power ",138,268,19,BLACK);
				DrawText(" the number up there on the left ",138,288,19,RED);
				DrawText(" Don't let it fall too low or you'll lose your job !",138,308,19,BLACK);
				(*talkcounter)++;
				Color color;
				if(*talkcounter%30 <15){
					color = BLACK;
				}else{
					color = RED;
				}
				DrawText("3",53,0+sin((float)*talkcounter/10 + 1.5)*10+7,25,color);
				DrawText("0",55+MeasureText("3",25),0+sin((float)*talkcounter/10+1.8)*10+7,25,color);
				DrawText("0",54+MeasureText("30",25),0+sin((float)*talkcounter/10+2.1)*10+7,25,color);
			//	DrawText(" factories to cities you find, your job is done once they are ALL GONE",138,308,19,BLACK);
			//	DrawText(" got that ? Perfect!",138,328,19,BLACK);
				DrawText(" Press enter to continue",538,358,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 4;
				}
				break;
			case 4:
				DrawText(" Your first power is ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("ra  in",*talkcounter,138+MeasureText(" Your first power is ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" Rain cost 25 and make the tiles fertile",138,66,19,BLACK);
				DrawText(" got that ? Perfect!",138,86,19,RED);
				DrawText(" rain works only on BARREN land",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 5;
				}
				break;
			case 5:
				DrawText(" Your first power is ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("ra  in",*talkcounter,138+MeasureText(" Your first power is ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" Rain cost 25 and make the tiles fertile",138,66,19,BLACK);
				DrawText(" rain works only on BARREN land",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 6;
				}
				break;
			case 6:
				DrawText(" After rain comes ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("grass",*talkcounter,138+MeasureText(" After rain comes ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" grass cost 100 and make the tiles grassy",138,66,19,BLACK);
				DrawText(" Grass works only on fertile land AND GIVES POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 7;
				}
				break;
			case 7:
				DrawText(" After rain comes ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("grass",*talkcounter,138+MeasureText(" After rain comes ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" grass cost 100 and make the tiles grassy",138,66,19,BLACK);
				DrawText(" Grass works only on fertile land AND GIVES POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 8;
				}
				break;
			case 8:
				DrawText(" Cool it's all Grass now for some ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("FOREST",*talkcounter,138+MeasureText(" Cool it's all Grass now for some ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" forest cost 200 and make the tiles foresty",138,66,19,BLACK);
				DrawText(" forest works only on grassy land AND GIVES A LOT OF POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 9;
				}
				break;
			case 9:
				DrawText(" Cool it's all Grass now for some ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("FOREST",*talkcounter,138+MeasureText(" Cool it's all Grass now for some ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" forest cost 100 and make the tiles grassy",138,66,19,BLACK);
				DrawText(" forest works only on grassy land AND GIVES A LOT OF POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 10;
				}
				break;
			case 10:
				DrawText(" Same as forests you can use ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("JUNGLE",*talkcounter,138+MeasureText(" Cool it's all Grass now for some ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" forest cost 200 and make the tiles foresty",138,66,19,BLACK);
				DrawText(" jungle works only on grassy land AND GIVES A LOT OF POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 11;
				}
				break;
			case 11:
				DrawText(" Same as forests you can use ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("JUNGLE",*talkcounter,138+MeasureText(" Cool it's all Grass now for some ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" jungle cost 100 and make the tiles grassy",138,66,19,BLACK);
				DrawText(" jungle works only on grassy land AND GIVES A LOT OF POINTS BACK !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 12;
				}
				break;
			case 12:
				DrawText(" Now for the ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("PESKY HUMANS",*talkcounter,138+MeasureText(" Now for the ",19),26);
				DrawText(" Look at their sad cities and polluted lands ",138,46,19,BLACK);
				DrawText(" Don't you agree a cleaning is in order",138,66,19,BLACK);
				DrawText(" So let's show'em how angry mother earth is feeling",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 13;
				}
				break;
			case 13:
				DrawText(" A little ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("EARTHQUAKE",*talkcounter,138+MeasureText(" A little ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" earthquakes DON'T give points so be careful !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 14;
				}
				break;
			case 14:
				DrawText(" A little ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("EARTHQUAKE",*talkcounter,138+MeasureText(" A little ",19),26);
				DrawText(" The highlighted area is where the effect is gonna happen ",138,46,19,BLACK);
				DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" earthquakes DON'T give points so be careful !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 15;
				}
				break;
			case 15:
				DrawText(" the worst humanity creation ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
			//	DrawText(" earthquakes DON'T give points so be careful !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 16;
				}
				break;	
			case 16:
				DrawText(" the worst humanity creation ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
			//	DrawText(" earthquakes DON'T give points so be careful !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 17;
				}
				break;	
			case 17:
				DrawText(" the worst humanity creation ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
			//	DrawText(" earthquakes DON'T give points so be careful !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 18;
				}
				break;
			case 18:
				DrawText(" the worst humanity creation ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" so make sure TO SMASH THEM !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 19;
				}
				break;
			case 19:
				DrawText(" the worst humanity creation ",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" so make sure TO SMASH THEM !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 20;
				}
				break;
			case 20:
				DrawText(" This place needs some grass ",138,26,19,BLACK);
				(*talkcounter)++;
			/*	DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" so make sure TO SMASH THEM !",138,86,19,RED);*/
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 21;
				}
				break;
			case 21:
				DrawText(" Far better now ! ! !",138,26,19,BLACK);
				(*talkcounter)++;
			/*	DancingText("THE FACTORY",*talkcounter,138+MeasureText(" the worst humanity creation ",19),26);
				DrawText(" factory produce so much heat the lands around them stays barren ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" so make sure TO SMASH THEM !",138,86,19,RED);*/
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 22;
				}
				break;
			case 22:
				DrawText(" now waters are all contaminated because of",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE OIL MACHINES",*talkcounter,138+MeasureText(" now waters are all contaminated because of",19),26);
				DrawText(" destroy them all and water will be cleansed ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
			//	DrawText(" WHY DONT WE SHOW'EM HOW ITS DONE !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 23;
				}
				break;
			case 23:
				DrawText(" now waters are all contaminated because of",138,26,19,BLACK);
				(*talkcounter)++;
				DancingText("THE OIL MACHINES",*talkcounter,138+MeasureText(" now waters are all contaminated because of",19),26);
				DrawText(" destroy them all and water will be cleansed ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" WHY DONT WE SHOW'EM HOW ITS DONE !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 24;
				}
				break;
			case 24:
				DrawText(" How wonderful, Clean water ! !",138,26,19,BLACK);
				(*talkcounter)++;
			//	DancingText("THE OIL MACHINES",*talkcounter,138+MeasureText(" now waters are all contaminated because of",19),26);
			//	DrawText(" destroy them all and water will be cleansed ",138,46,19,BLACK);
			//	DrawText(" earthquake cost 400 and will destroy cities",138,66,19,BLACK);
				DrawText(" cleaning water will give you lots of points so be sure to do it !",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 25;
				}
				break;
			case 25:
				DrawText(" NOW, you are ready to start your job",138,26,19,BLACK);
				(*talkcounter)++;
			//	DancingText("THE OIL MACHINES",*talkcounter,138+MeasureText(" now waters are all contaminated because of",19),26);
				DrawText(" I'll keep an eye on you so make sure you dont lose all your points ",138,46,19,BLACK);
				DrawText(" good luck dearest architect, Don't disappoint me <3",138,66,19,BLACK);
				DrawText(" left click to move camera and right click to use power",138,86,19,RED);
				DrawText(" Press enter to continue",538,116,19,BLACK);
				if(IsKeyPressed(KEY_ENTER)){
					*talk = 26;
				}
				break;																													
		//DrawText(" and endless expansion,",138,300,19,BLACK);
		}
		if(*talk <4){
			DrawRectangle(10,260,128,128,LIME);		
			DrawTexture(mommy,10,260,WHITE);
			DrawRectangleLinesEx((Rectangle){10,260,128,128},3,DARKGREEN);
		}else{
			DrawRectangle(10,10,128,128,LIME);		
			DrawTexture(mommy,10,010,WHITE);
			DrawRectangleLinesEx((Rectangle){10,10,128,128},3,DARKGREEN);
		}
		return false;
}
