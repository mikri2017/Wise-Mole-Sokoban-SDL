#include "Scene.h"

std::string Scene::get_name()
{
	return name;
}

bool Scene::set_name(std::string s_name)
{
	if (s_name == "")
		return false;

	name = s_name;
	return true;
}
