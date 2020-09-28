#include <iostream>
#include <Windows.h>
#include "GameObjects.h"

struct GameObject {
	char* name;
	int id;
};

bool GameObjects::CreateGameObject()
{
	printf("Object Created !\n");

	return true;
}

bool GameObjects::RemoveGameObject()
{
	printf("Object Removed !\n");

	return true;
}
