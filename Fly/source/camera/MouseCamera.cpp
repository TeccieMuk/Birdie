#include "camera/mousecamera.h"
#include <glm/ext/matrix_transform.hpp>
#include <functional>

MouseCamera::MouseCamera(KeyboardHandler& keyboardHandler, MouseHandler& mouseHandler) {
	keyboardHandler.addPressHandler(GLFW_KEY_W, std::bind(&MouseCamera::moveForward, this, std::placeholders::_1));
	keyboardHandler.addPressHandler(GLFW_KEY_S, std::bind(&MouseCamera::moveBack, this, std::placeholders::_1));
	keyboardHandler.addPressHandler(GLFW_KEY_A, std::bind(&MouseCamera::moveLeft, this, std::placeholders::_1));
	keyboardHandler.addPressHandler(GLFW_KEY_D, std::bind(&MouseCamera::moveRight, this, std::placeholders::_1));
	mouseHandler.addMouseCoordCallback(std::bind(&MouseCamera::updateMouseCoords, this, std::placeholders::_1, std::placeholders::_2));
}

void MouseCamera::updateMouseCoords(float xpos, float ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

glm::mat4 MouseCamera::getView(float time, float timeDelta) {
	return glm::lookAt(CameraPos, CameraPos + cameraFront, cameraUp);
}

glm::vec3 MouseCamera::getPosition()
{
	return CameraPos;
}

void MouseCamera::moveForward(float elapsedTime){
	float cameraSpeed = speed * elapsedTime;
	CameraPos += cameraSpeed * cameraFront;
}
void MouseCamera::moveBack(float elapsedTime) {
	float cameraSpeed = speed * elapsedTime;
	CameraPos -= cameraSpeed * cameraFront;
}
void MouseCamera::moveLeft(float elapsedTime) {
	float cameraSpeed = speed * elapsedTime;
	CameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void MouseCamera::moveRight(float elapsedTime) {
	float cameraSpeed = speed * elapsedTime;
	CameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}