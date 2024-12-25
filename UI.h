#pragma once
#include "Utils.h"

bool Button(const char* text, int x, int y, int width, int height, int font);
bool ButtonTexture(int x, int y, int width, int height, Texture2D texture);
bool ButtonDance(int x, int y, int width, int height, Texture2D texture, int counter);
bool Tutorial(int* talk, int* talkcounter, Texture2D mommy,Texture2D dommy);
