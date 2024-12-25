#pragma once
#include "Utils.h"

int StartMenuBefore(Texture2D Start,int height,int width,int *state);
void AnimateRectangle(Rectangle * Start,int counter,float direction);
int LogoScreen(Texture2D Start,Sound sea, Sound seagull);
void StillMenu(Texture2D Start,int height,int width);
