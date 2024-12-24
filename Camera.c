#include "Camera.h"

void CameraMove(Camera2D * Camera) {
	

    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f/Camera->zoom);
    Camera->target = Vector2Add(Camera->target, delta);
    
}

void FixCamera(Camera2D * Camera){
	if(Camera->target.x > 1000){
    	Camera->target.x -= (Camera->target.x-1000)/50;
	}else if(Camera->target.x < -1000){
		Camera->target.x -= (Camera->target.x+1000)/50;
	}
	if(Camera->target.y > 850){
    	Camera->target.y -= (Camera->target.y-850)/50;
	}else if(Camera->target.y < -200){
		Camera->target.y -= (Camera->target.y+200)/50;
	}
}

void CameraMoveBorder(Camera2D * Camera,int height,int width) {
    Vector2 offseter =GetMouseDelta();
    printf("the x is : %f and they y is : %f \n",offseter.x,offseter.y);
    Vector2 mouse = GetMousePosition();
    Vector2 delta = {0,0};

    if(mouse.x>=width-10){

        if(offseter.y>0){
            delta.y+=3;
        }
        else if(offseter.y<0){
            delta.y-=3;
        }

        delta.x+=3;
    }
    if(mouse.x<=10){
             if(offseter.y>0){
            delta.y+=3;
        }
        else if(offseter.y<0){
            delta.y-=3;
        }
        delta.x-=3;
    }
    if(mouse.y>=height-10){
        if(offseter.x>0){
            delta.x+=3;
        }
        else if(offseter.x<0){
            delta.x-=3;
        }
        delta.y+=3;
    }
    if(mouse.y<=10 ){
            if(offseter.x>0){
            delta.x+=3;
        }
        else if(offseter.x<0){
            delta.x-=3;
        }
        delta.y-=3;
    }


    delta = Vector2Scale(delta,1.0f * 5.0f/Camera->zoom );
    Camera->target=Vector2Add(Camera->target,delta);

}

/*bool MouseOnBorder(int width,int height) {
    Vector2 mouse = GetMousePosition();
    //printf("mouse y : %f \n",mouse.y);

    if(mouse.x>=width-3 || mouse.x<=3 || mouse.y<=3 || mouse.y>=height-3) {
        return true;
    }
    else {
        return false;
    }
}*/
