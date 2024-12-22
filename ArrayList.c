#include "ArrayList.h"


ArrayList* CreateArrayList(int TypeSize,int InitialSize){
	ArrayList* list = malloc(sizeof(ArrayList));
	bool check = list != NULL;
	ASSERT(check,"Couldn't allocate list");
	list->List = malloc(TypeSize*InitialSize);
	check = list->List != NULL;
	ASSERT(check,"Couldn't allocate items");
	list->length = 0;
	list->Size = InitialSize;
	list->TypeSize = TypeSize;
	return list; 
}

int AddItem(ArrayList* list,void* item){
	if(list->length == list->Size){
		list->Size = list->Size == 0 ? 1 : list->Size*2;
		void* items = realloc(list->List,list->Size*list->TypeSize);
		bool check = items != NULL;
		ASSERT(check,"Couldn't allocate memory for new item in arraylist");
		list->List = items;
	}

	memcpy(list->List + list->TypeSize*list->length, item, list->TypeSize);
	//list->List + list->TypeSize * list->length = item;
	return list->length++;
	
}

void* GetItem(ArrayList* list, int Id){
	bool check = list->length > Id;
	if(!check)
		printf("||%d:%d||\n",list->length , Id);
	ASSERT(check, "indexing out of bound-arraylist");
//	printf("%p\n",list->List + list->TypeSize * Id);
	return  list->List + list->TypeSize * Id;
}

void RemoveItem(ArrayList* list, int Id){
	if(Id != list->length-1){
		memcpy(list->List + list->TypeSize*Id, list->List + list->TypeSize*(Id+1), list->TypeSize* (list->length - Id));
	}
	list->length--;
	if(list->length < list->Size/2.0 && list->Size != 1){
		void* items = realloc(list->List,list->Size*list->TypeSize/2);
		list->Size = list->Size/2;
		ASSERT(items,"Couldn't allocate memory after deletion in arraylist");
		list->List = items;
	}
}
