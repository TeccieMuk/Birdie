#pragma once
#include "shader.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include "camera.h"
#include "ThinkThing.h"
#include "Object.h"

class Bird : public ThinkThing, public Object
{
public:
	Bird(glm::vec3 position, glm::vec3 direction);
	~Bird();
	void think(long timeDeltaMsec, long long timeAbsoluteMsec) override;
	void tick(float time, float deltaTime);
	void render(
		float time,
		glm::mat4& viewMatrix,
		glm::mat4& projectionMatrix,
		Camera& camera,
		glm::vec3 lightPos,
		glm::vec3 lightColor);

public:
	glm::vec3 destination = glm::vec3(0, 2, 0);

private:
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	Shader* shader = nullptr;
	long long lastTick = 0;
	long timeBetweenDirectionChanges = 10000;
	float speed = 0.7f;
	float rotation = 0;
	float rotationSpeed = 0.3f;
	float angle = 0.0f;
	glm::vec2 fieldSize = glm::vec2(20, 20);
};