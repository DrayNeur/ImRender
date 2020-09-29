#pragma once
#include <vector>

class GameObjects
{
	public:
		static struct GameObject
		{
			int id;
		};
		static bool CreateGameObject(int id);
		static bool RemoveGameObject();
		static bool InitGameObject();
		static std::vector<GameObject> getGameObjects();
};