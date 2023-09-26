#pragma once
#include "utility/shader.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "camera/Camera.h"
#include "logic/ThinkThing.h"
#include "objects/Object.h"
#include "behaviors/BehaviorTarget.h"

class Bird : public Object, public BehaviorTarget
{
public:
	Bird(glm::vec3 position, glm::vec3 direction);
	~Bird();
	void tick(float time, float deltaTime);
	void render(
		float time,
		glm::mat4& viewMatrix,
		glm::mat4& projectionMatrix,
		Camera& camera,
		glm::vec3 lightPos,
		glm::vec3 lightColor);

public:
	glm::vec3 getDestination() { return destination; }
	void setDestination(glm::vec3 destination) override { this->destination = destination; }

private:
	glm::vec3 destination = glm::vec3(0, 2, 0);
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	Shader* shader = nullptr;
	float speed = 0.7f;
	float rotation = 0;
	float rotationSpeed = 0.3f;
	float angle = 0.0f;
};