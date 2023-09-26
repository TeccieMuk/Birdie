#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <functional>
#include <GLFW/glfw3.h>


class MouseHandler
{
public:
	MouseHandler() = default;
	~MouseHandler() = default;

	void addMouseCoordCallback(std::function<void(float, float)>);
	void handleMouseCoords(float xpos, float ypos);

private:
	std::vector<std::function<void(float, float)>> mouseCoordCallbacks;
};