#include "utility/KeyboardHandler.h"

void KeyboardHandler::addPressHandler(int key, std::function<void(float)> callback)
{
	if (pressCallbacks.find(key) == pressCallbacks.end())
	{
		// Does this fall out of scope?
		auto vector = new std::vector<std::function<void(float)>>();
		pressCallbacks.insert({ key, vector });
	}

	pressCallbacks[key]->push_back(callback);
}

void KeyboardHandler::addReleaseHandler(int key, std::function<void(float)> callback)
{
	if (releaseCallbacks.find(key) == pressCallbacks.end())
	{
		// Does this fall out of scope?
		auto vector = new std::vector<std::function<void(float)>>();
		releaseCallbacks.insert({ key, vector });
	}

	releaseCallbacks[key]->push_back(callback);
}

void KeyboardHandler::handleKeyboard(GLFWwindow* window, float elapsedTime)
{
	for (auto assignment : pressCallbacks)
	{
		if (glfwGetKey(window, assignment.first) == GLFW_PRESS)
		{
			for (auto callback : *assignment.second)
			{
				callback(elapsedTime);
			}
		}
	}
}