#pragma once
#include <iostream>

class ProjectManager
{
public:
	static bool openProject(std::string path);
	static bool createProject(std::string path);
	static char* getProjectPath();
};

