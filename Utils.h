#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "include/raylib.h"
#include "include/raymath.h"

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED
#endif

//add all utilities standard libraries here
//any macros that generally help can be added here

#define ASSERT(x,y) if(!x){ printf("\n%s: %s",__TIME__,y); exit(-1);}
#define NEW(x,y)  malloc(sizeof(x)*y);
#define MIN(x,y) x > y ? y : x
#define MAX(x,y) x < y ? y : x
#define SIGN(x) x>0?1:(x<0?-1:0)

#define WORLDSIZE 64

