#pragma once
#include "Utils.h"

void CameraMove(Camera2D * Camera);
void FixCamera(Camera2D * Camera);
void CameraMoveBorder(Camera2D * Camera,int height,int width) ;
bool MouseOnBorder(int width,int height);
