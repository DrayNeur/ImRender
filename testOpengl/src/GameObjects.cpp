#include <iostream>
#include <Windows.h>
#include <iostream>
#include <fstream> 
#include <string>
#include <filesystem>
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
std::vector<std::string> getJson(std::string folder);
bool GameObjects::PopulateGameObjects()
{
	std::vector<std::string> files = getJson(ProjectManager::getProjectPath() + "\\gameObjects\\");
	for (std::string file : files) {
		std::ifstream ifs(ProjectManager::getProjectPath() + "\\gameObjects\\" + file);
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
	}
	return true;
}
std::vector<std::string> getJson(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.json";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
std::vector<GameObjects::GameObject> GameObjects::getGameObjects()
{
	return gameObjects;
}
