#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <functional>
#include <GLFW/glfw3.h>


class KeyboardHandler
{
public:
	KeyboardHandler() = default;
	~KeyboardHandler() = default;

	void addPressHandler(int key, std::function<void(float)>);
	void addReleaseHandler(int key, std::function<void(float)>);
	void handleKeyboard(GLFWwindow* window, float elapsedTime);

private:
	std::map<int, std::vector<std::function<void(float)>>*> pressCallbacks;
	std::map<int, std::vector<std::function<void(float)>>*> releaseCallbacks;
};