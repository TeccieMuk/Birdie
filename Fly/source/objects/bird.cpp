#include "objects/Bird.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Bird::Bird(glm::vec3 position, glm::vec3 direction) : Object(position, direction)
{
	float vertices[] = {
		-0.5f, 0,  0.5f, 1,
		-0.5f, 0,  0,    0,
		 0.5f, 0,  0,    0,
		-0.5f, 0, -0.5f, 1
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// IsWingtip attribute
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	shader = new Shader("shaders/birdShader.vs", "shaders/birdShader.fs");
}

Bird::~Bird() {
	if (shader != nullptr) {
		delete shader;
	}
}

void Bird::render(
	float time,
	glm::mat4& viewMatrix,
	glm::mat4& projectionMatrix,
	Camera& camera,
	glm::vec3 lightPos,
	glm::vec3 lightColor)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec4 x = glm::vec4(direction.x, direction.y, direction.z, 0);
	model[0] = x;
	glm::vec3 y = glm::cross(glm::vec3(0, 0, 1), direction);
	model[1] = glm::vec4(y.x, y.y, y.z, 0);
	y = normalize(y);
	glm::vec3 z = glm::cross(direction, y);
	model[2] = glm::vec4(z.x, z.y, z.z, 0);
	model[3] = glm::vec4(position.x, position.y, position.z, 1);

	shader->use();
	shader->setMatrix("model", model);
	shader->setMatrix("view", viewMatrix);
	shader->setMatrix("projection", projectionMatrix);
	shader->setVec3("lightColor", lightColor);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", camera.getPosition());
	shader->setFloat("time", time);
	shader->setFloat("flapSpeed", 2);

	// Rendering
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Bird::tick(float time, float timeDelta)
{
	// You are on an intercept path if horizontal component of the direction towards
	// the target does not change.
	// Take the cross product of the direction towards destination and the y up axis to get the
	// perpendicular cross.Compare this to the previous one, and use the cross product to
	// determine which way to rotate.

	glm::vec3 towardsNotNormalized = destination - position;
	glm::vec3 towardsNormalized = glm::normalize(towardsNotNormalized);

	// Check whether target is behind you.
	float dot = glm::dot(direction, towardsNormalized);
	glm::vec3 horizontalCross = glm::cross(towardsNotNormalized, glm::vec3(0, 1, 0));
	if (dot > 0)
	{
		glm::vec3 difference = horizontalCross - previousCrossFromDirection;
		glm::vec3 rotationCross = glm::cross(difference, previousCrossFromDirection);
		if (rotationCross.y < 0)
		{
			rotation += rotationSpeed * timeDelta;
		}
		else if (rotationCross.y > 0)
		{
			rotation -= rotationSpeed * timeDelta;
		}
	}
	// If we're behind the target, just turn into direction
	else
	{
		// Check which direction to turn...
		glm::vec3 cross = glm::cross(towardsNormalized, direction);

		if (cross.y < 0)
		{
			rotation += rotationSpeed * timeDelta;
		}
		else if (cross.y > 0)
		{
			rotation -= rotationSpeed * timeDelta;
		}
	}

	previousCrossFromDirection = horizontalCross;

	glm::mat4 rotateToTarget = glm::mat4(1.0f);
	rotateToTarget = glm::rotate(rotateToTarget, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 rotationVector = glm::vec4(-1, 0, -1, 0);
	direction = normalize(rotateToTarget * rotationVector);

	float distanceTravelled = timeDelta * speed;
	position += direction * distanceTravelled;
}

