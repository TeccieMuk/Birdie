#pragma once
#include <objects/Object.h>
#include <camera/Camera.h>
#include <utility/shader.h>

class Box : public Object
{
public:
	Box(glm::vec3 position, glm::vec3 direction);
	~Box();

	void render(
		float time,
		glm::mat4& viewMatrix,
		glm::mat4& projectionMatrix,
		Camera& camera,
		glm::vec3 lightPos,
		glm::vec3 lightColor);

private:
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	unsigned int nrTriangles;
	Shader* shader = nullptr;
};