#include <iostream>
#include <Windows.h>
#include <iostream>
#include <fstream> 
#include <vector>
#include "GameObjects.h"
#include "ProjectManager.h"
#include <json/json.h>
std::vector<GameObjects::GameObject> gameObjects;

bool GameObjects::CreateGameObject(char* name, int id)
{
	std::map<std::string, std::string> test;
	std::string name_str(name);
	std::string id_str = std::to_string(id);
	test["name"] = name_str;
	test["id"] = id_str;

	std::string mapString = ToJSON(test);
	std::string path_project = ProjectManager::getProjectPath();
	path_project += "\\gameObjects\\" + name_str + ".json";
	std::ofstream outfile(path_project);

	outfile << mapString << std::endl;

	outfile.close();
	printf(mapString.c_str());
	return true;
}

bool GameObjects::RemoveGameObject()
{
	printf("Object Removed !\n");

	return true;
}
bool GameObjects::PopulateGameObjects()
{
	printf("Object init !\n");
	return true;
}

std::vector<GameObjects::GameObject> GameObjects::getGameObjects()
{
	return gameObjects;
}
