#include "Menu.h"
#include "Utils.h"


int StartMenuBefore(Texture2D Start,int height,int width,int *state){
    bool b = true;
    int Press=-1;
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
    Vector2 f={0,50};

    Rectangle StartButton;
    Rectangle Map[3];

    //initialize the map buttons
    for(int i =0 ; i<3;i++){
        Map[i].height=75;
        Map[i].width=150;
        Map[i].x=width/2 - 350 + i * 275;
        Map[i].y=height;
    }

   if((*state)==-1 || (*state)<=180) {
    //Rectangle StartButton;
    StartButton.height=75;
    StartButton.width= 200;
    StartButton.x=width/2 -100;
    StartButton.y=height-100;
   }

    Color Border= WHITE;

    Vector2 mouse = GetMousePosition();
    //printf("i got here \n");

    if(CheckCollisionPointRec(mouse,StartButton)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    printf("i got here \n");
                b=false;
            }
        Border=RED;
    }

    if (!b){
        (*state) = 0;
    }

    if((*state)!=-1 && (*state)<=180){

            if((*state)<30){
                AnimateRectangle(&StartButton,(*state),0.4);
            }
            else {
                AnimateRectangle(&StartButton,(*state),-0.1);
            }

        //AnimateRectangle(&StartButton, (*state));
        //AnimateRectangle(&Map[0],(*state)-1,1);
        (*state)++;
    }


    for(int i=0;i<3;i++) {

        /*if(Map[i].y>height-100) {
            AnimateRectangle(&Map[i],(*state),0.1);
        }
        if(Map[i].y<height-100){
            Map[i].y=height-100;
        }*/

        if((*state)>120 +i*120) {
            (*state)++;
            if(Map[i].y>height-100) {
                AnimateRectangle(&Map[i],(*state),(float)1/(100+i*100));
            }
            if(Map[i].y<height-100){
            Map[i].y=height-100;
            }

        }

    }

  for(int i=0;i<3;i++){

        if(CheckCollisionPointRec(mouse,Map[i])){
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    printf("i pressed a button ! %d \n",i);
                    Press=i;
                }
                printf("collision");

            Border=RED;
        }

    }


    //DrawTexture(Start,0,0,WHITE);
    BeginDrawing();
    ClearBackground(SKYBLUE);

    DrawTexturePro(Start,s,v,f,0.0f,WHITE);

    if((*state)==-1 || (*state)<=180){
    DrawRectangleLinesEx(StartButton,3.0f,Border);
    DrawText("START",StartButton.x+48,StartButton.y+23,30,WHITE);
    }

    for(int i =0;i<3;i++){
        DrawRectangleLinesEx(Map[i],3.0f,Border);
        DrawText("LEVEL 1",Map[0].x+20,Map[0].y+23,28,WHITE);
        DrawText("LEVEL 2",Map[1].x+20,Map[1].y+23,28,WHITE);
        DrawText("LEVEL 3",Map[2].x+20,Map[2].y+23,28,WHITE);
    }


    //DrawTexture(Start,0,0,WHITE);
    EndDrawing();
    return Press;
}

void AnimateRectangle(Rectangle * Start,int counter,float direction){


        float yoffset = -(counter/5 -1)*(counter/5 -1)+1;

        yoffset *=direction;
        /*yoffset*=0.3;

        if(counter >30) {
            yoffset *=-0.5;
        }*/

        Start->y+=yoffset;

}

