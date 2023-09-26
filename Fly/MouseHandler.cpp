#include "MouseHandler.h"

void MouseHandler::addMouseCoordCallback(std::function<void(float, float)> callback)
{
	mouseCoordCallbacks.push_back(callback);
}

void MouseHandler::handleMouseCoords(float xpos, float ypos)
{
	for (auto callback : mouseCoordCallbacks)
	{
		callback(xpos, ypos);
	}
}