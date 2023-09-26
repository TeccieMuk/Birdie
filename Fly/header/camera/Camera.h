#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera() = default;
	virtual ~Camera() = default;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::mat4 getView(float time, float timeDelta) = 0;
};