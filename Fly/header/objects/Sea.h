#pragma once
#include "utility/shader.h"
#include "camera/Camera.h"

const unsigned int NR_WAVES = 100;
const float DISTANCE_APART = 1;
const float X_VARIATION = 0.1f;
const float WAVE_LENGTH = 5;

class Sea
{
public:
	Sea();
	~Sea();
	void render(
		float time,
		glm::mat4& viewMatrix,
		glm::mat4& projectionMatrix,
		Camera& camera,
		glm::vec3 lightPos,
		glm::vec3 lightColor);

private:
	glm::mat4 model = glm::mat4(1.0f);
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	Shader* shader;
	unsigned int indices[(NR_WAVES - 1) * (NR_WAVES - 1) * 6] = {};
	float vertices[NR_WAVES * NR_WAVES * 3] = {};
};