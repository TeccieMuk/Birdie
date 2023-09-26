#include "SkyBox.h"
#include "stb_image.h"

SkyBox::SkyBox()
{
	std::vector<std::string> faces
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};
	cubemapTexture = loadCubemap(faces);
	shader = new Shader("skyboxShader.vs", "skyboxShader.fs");
	float skyboxVertices[] = {
		// positions          
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,

		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE,  SKYBOX_SIZE,
		-SKYBOX_SIZE,  SKYBOX_SIZE, -SKYBOX_SIZE,

		-SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE, -SKYBOX_SIZE,
		-SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE,
		 SKYBOX_SIZE, -SKYBOX_SIZE,  SKYBOX_SIZE
	};
	unsigned int skyvbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &skyvbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, skyvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

SkyBox::~SkyBox()
{
	delete shader;
}

void SkyBox::render(
	float time,
	glm::mat4& viewMatrix,
	glm::mat4& projectionMatrix,
	Camera& camera,
	glm::vec3 lightPos,
	glm::vec3 lightColor)
{
	glDepthMask(GL_FALSE);
	shader->use();
	glm::mat4 skyboxView = glm::mat4(glm::mat3(viewMatrix));
	shader->setMatrix("view", skyboxView);
	shader->setMatrix("projection", projectionMatrix);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
}

unsigned int SkyBox::loadCubemap(std::vector<std::string>& faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}