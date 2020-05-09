#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Shader.h"
#include "Entity.h"
#include "TexturedModel.h"
#include "TexturedEntity.h"

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
	// Load cube model
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	TexturedModel cubeModel;
	cubeModel.loadVertexData(vertices, 36);
	cubeModel.loadTexture("../Testgl/res/texture/test.png");
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	TexturedEntity cubes[10];
	for (unsigned int i = 0; i < 10; i++)
	{
		cubes[i] = TexturedEntity(&cubeModel, cubePositions[i]);
		cubes[i].updateModelMatrix();
	}

	// Load Shaders
	fontShader.load("../Testgl/res/shader/text.vert", "../Testgl/res/shader/text.frag");
	simpleShader.load("../Testgl/res/shader/simple.vert", "../Testgl/res/shader/simple.frag");

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
		
		// Camera
		simpleShader.use();
		glm::mat4 projection(1.0f);
		projection = glm::perspective(glm::radians(camera.fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		simpleShader.setMat4("projection", projection);
		simpleShader.setMat4("view", camera.getView());
		// Draw scene
		cubes[0].model->bind();
		simpleShader.setInt("tex", 0);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			simpleShader.setMat4("model", cubes[i].modelMatrix);
			cubes[i].model->draw();
		}

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
		camera.rotation = camera.rotation * glm::angleAxis(glm::radians(xoffset * MOUSE_SENSITIVITY), glm::vec3(0.0f, 0.0f, 1.0f));
		// Rotate then pitch -> pitch should add to existing pitch
		camera.rotation = glm::angleAxis(glm::radians(yoffset * MOUSE_SENSITIVITY), glm::vec3(0.0f, 1.0f, 0.0f)) * camera.rotation;
		
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
	if (camera.fov >= 1.0f && camera.fov <= 75.0f)
		camera.fov -= (float)yoffset;
	if (camera.fov <= 1.0f)
		camera.fov = 1.0f;
	if (camera.fov >= 75.0f)
		camera.fov = 75.0f;
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
