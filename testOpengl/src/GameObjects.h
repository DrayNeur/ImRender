#pragma once
#include <vector>

class GameObjects
{
	public:
		static struct GameObject
		{
			char* name;
			int id;
		};
		static bool CreateGameObject(char* name, int id);
		static bool RemoveGameObject();
		static bool InitGameObject();
		static std::vector<GameObject> getGameObjects();
};