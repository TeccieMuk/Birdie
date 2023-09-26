#pragma once
#include <vector>
#include <string>
#include "shader.h"
#include "Camera.h"

const float SKYBOX_SIZE = 10;

class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void render(
		float time,
		glm::mat4& viewMatrix,
		glm::mat4& projectionMatrix,
		Camera& camera,
		glm::vec3 lightPos,
		glm::vec3 lightColor);

private:
	unsigned int loadCubemap(std::vector<std::string>& faces);

private:
	unsigned int vao;
	unsigned int cubemapTexture;
	Shader* shader;
};