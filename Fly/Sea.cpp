#include "sea.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Sea::Sea()
{
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	shader = new Shader("shader.vs", "shader.fs");

	float centerOffset = (NR_WAVES * DISTANCE_APART) / 2;
	for (int y = 0; y < NR_WAVES; y++)
	{
		for (int x = 0; x < NR_WAVES; x++)
		{
			float xRandomOffset = (((float)(rand() % 100) / 100) * (2 * X_VARIATION)) - X_VARIATION;
			float yRandomOffset = (((float)(rand() % 100) / 100) * (2 * X_VARIATION)) - X_VARIATION;
			int index = y * (NR_WAVES * 3) + x * 3;
			vertices[index] = (x * DISTANCE_APART) - centerOffset + xRandomOffset;
			vertices[index + 1] = (y * DISTANCE_APART) - centerOffset + yRandomOffset;
			vertices[index + 2] = 0;
		}
	}

	for (int y = 0; y < NR_WAVES - 1; y++)
	{
		for (int x = 0; x < NR_WAVES - 1; x++)
		{
			int currentIndexRow = y * ((NR_WAVES - 1) * 6) + x * 6;
			int currentVertexRow = y * NR_WAVES + x;
			int nextVertexRow = (y + 1) * NR_WAVES + x;

			indices[currentIndexRow] = currentVertexRow;
			indices[currentIndexRow + 1] = currentVertexRow + 1;
			indices[currentIndexRow + 2] = nextVertexRow + 1;
			indices[currentIndexRow + 3] = currentVertexRow;
			indices[currentIndexRow + 4] = nextVertexRow;
			indices[currentIndexRow + 5] = nextVertexRow + 1;
		}
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

Sea::~Sea()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	delete shader;
	shader = nullptr;
}

void Sea::render(
	float time,
	glm::mat4& viewMatrix,
	glm::mat4& projectionMatrix,
	Camera& camera,
	glm::vec3 lightPos,
	glm::vec3 lightColor)
{
	shader->use();
	shader->setMatrix("model", model);
	shader->setMatrix("view", viewMatrix);
	shader->setMatrix("projection", projectionMatrix);
	shader->setFloat("wave_time", time);
	shader->setFloat("wave_amp", 0.2f);
	shader->setFloat("wave_length", WAVE_LENGTH);
	shader->setFloat("wave_speed", 0.5f);
	shader->setVec3("lightColor", lightColor);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", camera.getPosition());

	// Rendering
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
