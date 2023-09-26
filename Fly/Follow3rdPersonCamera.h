#pragma once
#include "Object.h"
#include "Camera.h"

class Follow3rdPersonCamera: public Camera
{
public:
	Follow3rdPersonCamera(Object& objectToFollow) : target(objectToFollow) {}
	~Follow3rdPersonCamera() = default;

	void setTarget(Object& objectToFollow);
	glm::mat4 getView(float time, float timeDelta);
	glm::vec3 getPosition() override;

private:
	Object& target;
	float cameraDistance = 6;
	glm::vec3 lastPosition = glm::vec3(0, 0, 0);
	glm::vec3 lookingDirection = glm::vec3(1, 0, 0);
	float cameraRotateSpeed = 1;
	Follow3rdPersonCamera() = delete;
	Follow3rdPersonCamera(const Follow3rdPersonCamera& other) = delete;
};
