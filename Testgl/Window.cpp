#include "Window.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Shader.h"
#include "Entity.h"
#include "Model.h"
#include "TexturedModel.h"
#include "ColoredModel.h"
#include "Light.h"

Window::Window(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

Window::~Window()
{

}

void Window::init()
{
	window = glfwCreateWindow(screenWidth, screenHeight, "CUBOIDAL", NULL, NULL);
	if (window == nullptr) {
		std::cerr << "ERROR::GLFW::WINDOW_CREATION_FAILED" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "ERROR::GLAD::INIT_FAILED" << std::endl;
		return;
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, screenWidth, screenHeight);
	
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glfwSetCursorPosCallback(window, mouseMoveCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);

	// For font rendering
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	fontManager.loadFont("../Testgl/res/font/Anonymous Pro B.ttf");
}

void Window::run()
{
	// TODO: Move model management to separate class with entities organized based on model


	float lightCubeVerticies[] = {
		-0.5f, -0.5f, -0.5f,	
		 0.5f, -0.5f, -0.5f,	
		 0.5f,  0.5f, -0.5f,	
		-0.5f,  0.5f, -0.5f,	
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f
	};
	unsigned int lightCubeIndicies[] = {
		0, 1, 3, 3, 1, 2,
		1, 5, 2, 2, 5, 6,
		5, 4, 6, 6, 4, 7,
		4, 0, 7, 7, 0, 3,
		3, 2, 7, 7, 2, 6,
		4, 5, 0, 0, 5, 1
	};
	// Set up lights
	//ColoredModel lightModel;
	Model lightModel;
	lightModel.loadVertex(lightCubeVerticies, 8, 3, GL_STATIC_DRAW);
	lightModel.loadIndices(lightCubeIndicies, 36, GL_STATIC_DRAW);
	Light light1(glm::vec3(1.0f, 1.0f, 1.0f));
	light1.position = glm::vec3(-2.0f, 2.0f, -1.0f);
	light1.scale = glm::vec3(0.25f);
	light1.updateModelMatrix();

	// Load cube model
	float vertices[] = {
		// Z-
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f,

		// Z+
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 0.0f,

		// X-
		-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	1.0f, 0.0f,

		// X+
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	1.0f, 0.0f,

		// Y-
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f, 	1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f, 	1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f, 	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 1.0f,

		// Y+
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 1.0f,	0.0f, 	1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,	0.0f, 	1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,	0.0f, 	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 1.0f
	};
	TexturedModel cubeModel;
	cubeModel.loadVertexNormalTexture(vertices, 36, GL_STATIC_DRAW);
	//cubeModel.loadTexture("../Testgl/res/texture/test.png");
	cubeModel.loadTexture("../Testgl/res/texture/3crates/crate1/crate1_diffuse.png");
	glm::vec3 cubePositions[] = {
		glm::vec3(2.0f,  0.0f,  0.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -9.0f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
		glm::vec3(0.0f,  0.0f, -15.0f)
	};
	Entity cubes[10];
	for (unsigned int i = 0; i < 10; i++)
	{
		cubes[i] = Entity(cubePositions[i]);
		cubes[i].updateModelMatrix();
	}
	cubes[9].scale = glm::vec3(40.0f, 40.0f, 1.0f);
	cubes[9].updateModelMatrix();
	
	

	// Load Shaders
	fontShader.load("../Testgl/res/shader/text.vert", "../Testgl/res/shader/text.frag");
	simpleShader.load("../Testgl/res/shader/simple.vert", "../Testgl/res/shader/simple.frag");
	lightSourceShader.load("../Testgl/res/shader/lightsource.vert", "../Testgl/res/shader/lightsource.frag");

	// Capture cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glm::quat rotation = glm::angleAxis(0.5f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		frameCounter.update(glfwGetTime());

		// Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		simpleShader.use();
		// Lighting
		simpleShader.setVec3("lightColor", light1.color);
		simpleShader.setVec3("lightPos", light1.position);
		simpleShader.setVec3("viewPos", camera.position);
		// Camera
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera.fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		simpleShader.setMat4("projection", projection);
		simpleShader.setMat4("view", camera.getView());
		// Draw scene
		cubeModel.bind();
		simpleShader.setInt("tex", 0);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			simpleShader.setMat4("model", cubes[i].modelMatrix);
			cubeModel.draw();
		}
		// Light entities
		lightSourceShader.use();
		lightSourceShader.setMat4("projection", projection);
		lightSourceShader.setMat4("view", camera.getView());
		lightSourceShader.setMat4("model", light1.modelMatrix);
		lightModel.bind();
		lightModel.drawIndices();

		// Draw text
		fontShader.use();
		fontShader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight));
		glUniform3f(glGetUniformLocation(fontShader.ID, "textColor"), 1.0f, 1.0f, 1.0f);
		fontManager.drawText(std::to_string(frameCounter.fps), 25.0f, 25.0f, 0.5f);
		fontManager.drawText("pos: " + glm::to_string(camera.position), 25.0f, 200.0f, 0.5f);
		fontManager.drawText("rot: " + glm::to_string(camera.rotation), 25.0f, 175.0f, 0.5f);
		fontManager.drawText("up: " + glm::to_string(camera.up), 25.0f, 150.0f, 0.5f);
		fontManager.drawText("right: " + glm::to_string(camera.right), 25.0f, 125.0f, 0.5f);
		fontManager.drawText("front: " + glm::to_string(camera.forward), 25.0f, 100.0f, 0.5f);
		fontManager.drawText("fov: " + std::to_string(camera.fov), 25.0f, 75.0f, 0.5f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

#define MOUSE_SENSITIVITY 0.2f
#define CAMERA_SPEED 4.0f

double lastX, lastY;
bool firstMouse = true;

bool cursorCaptured = true;
bool spaceDown = false;
float lastTime = 0;

void Window::windowResized( int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);
}

void Window::mouseMoved(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = (float)(xpos - lastX);
	float yoffset = (float)(lastY - ypos); // Reverse y coords
	lastX = xpos;
	lastY = ypos;

	if (cursorCaptured) {
		// Yaw then rotate -> yaw should be independent of existing rotation (this prevents the camera from rolling)
		camera.rotateAbsolute(glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(xoffset * MOUSE_SENSITIVITY));
		// Rotate then pitch -> pitch should add to existing pitch
		camera.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(yoffset * MOUSE_SENSITIVITY));
		
		// Make sure screen doesn't get flipped by clamping pitch
		/*if (camera.rotation.y > 89.0f)
			camera.rotation.y = 89.0f;
		if (camera.rotation.y < -89.0f)
			camera.rotation.y = -89.0f;*/

		camera.updateDirection();
	}
}

void Window::mouseScrolled(double xoffset, double yoffset)
{
	if (camera.fov >= 1.0f && camera.fov <= 120.0f)
		camera.fov -= (float)yoffset;
	if (camera.fov <= 1.0f)
		camera.fov = 1.0f;
	if (camera.fov >= 120.0f)
		camera.fov = 120.0f;
	//camera.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(yoffset * 5.0f)); // Roll
	camera.updateDirection();
}

void Window::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	// Camera movement
	float timeNow = (float)glfwGetTime();
	float cameraMovement = CAMERA_SPEED * (timeNow - lastTime);
	lastTime = timeNow;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.position += cameraMovement * camera.forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.position -= cameraMovement * camera.forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.position -= glm::normalize(glm::cross(camera.forward, camera.up)) * cameraMovement;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.position += glm::normalize(glm::cross(camera.forward, camera.up)) * cameraMovement;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.position += cameraMovement * camera.up;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.position -= cameraMovement * camera.up;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		camera.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		camera.updateDirection();
	}
		
	// Cursor capture
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		spaceDown = false;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (!spaceDown)
		{
			spaceDown = true;
			glfwSetInputMode(window, GLFW_CURSOR, (cursorCaptured = !cursorCaptured) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}
	}
}
