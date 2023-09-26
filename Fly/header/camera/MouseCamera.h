#pragma once
#include "camera/Camera.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "utility/KeyboardHandler.h"
#include "utility/MouseHandler.h"

class MouseCamera: public Camera
{
public:
	MouseCamera(KeyboardHandler& keyboardHandler, MouseHandler& mouseHandler);

	glm::vec3 CameraPos = glm::vec3(0.0f, 5.0f, 3.0f);

    void updateMouseCoords(float xpos, float ypos);
	glm::mat4 getView(float time, float timeDelta);
	void moveForward(float elapsedTime);
	void moveBack(float elapsedTime);
	void moveLeft(float elapsedTime);
	void moveRight(float elapsedTime);
	glm::vec3 getPosition() override;

private:
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float yaw = -90.0f;
	float pitch = -90.0f;
	bool firstMouse = true;
	float lastX = 400, lastY = 300;

	const float speed = 2.5f;
};