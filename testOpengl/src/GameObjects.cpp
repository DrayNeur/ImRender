#include <iostream>
#include <Windows.h>
#include <vector>
#include "GameObjects.h"


std::vector<GameObjects::GameObject> gameObjects;

bool GameObjects::CreateGameObject(int id)
{
	gameObjects.push_back({ id });
	return true;
}

bool GameObjects::RemoveGameObject()
{
	printf("Object Removed !\n");

	return true;
}
bool GameObjects::InitGameObject()
{
	printf("Object init !\n");
	gameObjects.push_back({12});
	return true;
}

std::vector<GameObjects::GameObject> GameObjects::getGameObjects()
{
	return gameObjects;
}
