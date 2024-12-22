#pragma once
#include "Utils.h"
//array list type to use can handle any type of data 
typedef struct ArrayList{
	int length;
	int TypeSize;
	int Size;
	void* List;
} ArrayList;

ArrayList* CreateArrayList(int TypeSize,int InitialSize);
int AddItem(ArrayList* List,void* Item);
void* GetItem(ArrayList* list, int Id);
void RemoveItem(ArrayList* list, int Id);


