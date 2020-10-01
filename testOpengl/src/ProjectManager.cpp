#pragma warning(disable:4996)

#include "ProjectManager.h"
#include <direct.h>
#include <tchar.h>
#include <Windows.h>
const char* ProjectPath = "C:\\Users\\alyst\\source\\repos\\testOpengl\\ImRender\\projecttest";

bool ProjectManager::openProject(std::string path) {
	ProjectPath = path.c_str();
	return true;
}

bool ProjectManager::createProject(std::string path) {
	std::string orginal_path = path;
	path += "\\scripts";
	_tmkdir(path.c_str());
	path = orginal_path;
	path += "\\gameObjects";
	_tmkdir(path.c_str());
	path = orginal_path;
	path += "\\assets";
	_tmkdir(path.c_str());
	path = orginal_path;
	path += "\\build";
	_tmkdir(path.c_str());
	return true;
}
char* ProjectManager::getProjectPath() {
	return (char*)ProjectPath;
}