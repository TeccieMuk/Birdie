#include "utility/shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera/camera.h"
#include "objects/bird.h"
#include "logic/Brain.h"
#include "camera/Follow3rdPersonCamera.h"
#include "libraries/stb_image.h"
#include "camera/MouseCamera.h"
#include "objects/Sea.h"
#include "objects/SkyBox.h"
using namespace std;


// TODO all 'ticking' things should have their own interface that can be iterated over
// TODO Translucent water using blending

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
glm::vec3 lightPos(2.0f, 20.0f, 2.0f);

Camera* camera;
KeyboardHandler* keyboardHandler = new KeyboardHandler();
MouseHandler* mouseHandler = new MouseHandler();
Sea* sea;
SkyBox* skyBox;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	//---------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Fly", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Glad
	//---------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Enable for wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	// Transforms
	//---------------------------------
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	// Objects
	//---------------------------------
	Bird bird = Bird(glm::vec3(0, 2, 0), glm::vec3(1, 0, 0));
	Bird bird2 = Bird(glm::vec3(0, 2, 0), glm::vec3(1, 0, 0));
	Brain* brain = new Brain();
	brain->addThinkThing(&bird);
	sea = new Sea();
	skyBox = new SkyBox();

	// Camera
	//---------------------------------
	//camera = new MouseCamera(*keyboardHandler, *mouseHandler);
	camera = new Follow3rdPersonCamera(bird);

	// Main loop
	//---------------------------------	
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Clear
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Lights
		glm::vec3 lightColor = glm::vec3(1, 1, 1);

		// Action
		bird.tick(currentFrame, deltaTime);
		bird2.setPosition(bird.destination);

		// Camera
		glm::mat4 view = camera->getView(currentFrame, deltaTime);
		skyBox->render(currentFrame, view, projection, *camera, lightPos, lightColor);
		sea->render(currentFrame, view, projection, *camera, lightPos, lightColor);
		bird.render(currentFrame, view, projection, *camera, lightPos, lightColor);
		bird2.render(currentFrame, view, projection, *camera, lightPos, lightColor);

		// GLFW buffers and IO
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	delete brain;
	delete camera;
	delete keyboardHandler;
	delete sea;
	delete skyBox;
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	keyboardHandler->handleKeyboard(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseHandler->handleMouseCoords((float)xpos, (float)ypos);
}


