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
#include "Material.h"
#include "PointLight.h"
#include "SunLight.h"
#include "SpotLight.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Scene.h"

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
	scene.screenWidth = &screenWidth;
	scene.screenHeight = &screenHeight;

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
	// TODO: Lighting
	// 
	// Done - Multiple lights
	// Done - Materials
	// Done - Point light
	// Done - Spot Light
	// Done - Global (Sun) Light
	// Done - Specular map
	// - Normal Map
	// - Height Map
	// 

	TextureManager textureManager("../Testgl/res/texture/");
	
	// Single point light
	scene.pointLights.push_back(PointLight(glm::vec3(1.0f, 0.8f, 0.6f), 1.0f, 0.1f, 0.03f));
	scene.pointLights.push_back(PointLight(glm::vec3(1.0f, 1.0f, 0.2f), 1.0f, 0.1f, 0.03f));
	scene.pointLights.push_back(PointLight(glm::vec3(1.0f, 0.9f, 0.8f), 1.0f, 0.1f, 0.03f));

	// SunLight shining down, slightly from x,-y
	SunLight sun(glm::vec3(0.0f, 0.0f, 0.0f));
	sun.rotateAbsolute(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-75.0f));
	sun.rotateAbsolute(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(15.0f));
	scene.sunLights.push_back(sun);
	// SpotLight (a bit orangeish)
	SpotLight flashLight(glm::vec3(1.8f, 1.8f, 1.8f), 1.0f, 0.8f, 0.04f, glm::cos(glm::radians(10.0f)), glm::cos(glm::radians(16.0f)));
	flashLight.color = glm::vec3(0.0f);
	scene.spotLights.push_back(flashLight);

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
	float groundVertices[] = {
		// Z-
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	8.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	8.0f, 8.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,	8.0f, 8.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 8.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,	0.0f, 0.0f,

		// Z+
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	8.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	8.0f, 8.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 0.0f,	1.0f, 	8.0f, 8.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 8.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,	1.0f, 	0.0f, 0.0f,

		// X-
		-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	8.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	8.0f, 8.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 8.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 8.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f, 0.0f, 0.0f, 	8.0f, 0.0f,

		// X+
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	8.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	8.0f, 8.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 8.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 8.0f,
		0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f, 	8.0f, 0.0f,

		// Y-
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 8.0f,
		0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f, 	8.0f, 8.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f, 	8.0f, 0.0f,
		0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f, 	8.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f, 0.0f, 	0.0f, 8.0f,

		// Y+
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 8.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 1.0f,	0.0f, 	8.0f, 8.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,	0.0f, 	8.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		0.0f, 1.0f,	0.0f, 	8.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,	0.0f, 	0.0f, 8.0f
	};

	Material cubeMaterial(
		glm::vec3(0.1f, 0.1f, 0.1f), // Ambient
		glm::vec3(0.9f, 0.9f, 0.9f), // Diffuse
		glm::vec3(0.3f, 0.3f, 0.3f), // Specular
		8.0f); // Shine

	TexturedModel cubeModel;
	cubeModel.loadVertexNormalTexture(vertices, 36, GL_STATIC_DRAW);
	Texture* cubeTexture = textureManager.load("3crates/crate1");
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
		glm::vec3(0.0f,  0.0f, -14.0f)
	};
	for (unsigned int i = 0; i < 10; i++)
	{
		Entity cubeEntity(cubePositions[i], cubePositions[i]);
		cubeEntity.updateModelMatrix();
		scene.addEntity(TexturedEntity(cubeTexture, &cubeModel, &cubeMaterial, cubeEntity));
	}

	Entity groundEntity;
	groundEntity.position += glm::vec3(0.0f, 0.0f, -15.0f);
	groundEntity.scale = glm::vec3(40.0f, 40.0f, 1.0f);
	groundEntity.updateModelMatrix();
	TexturedModel groundModel;
	groundModel.loadVertexNormalTexture(groundVertices, 36, GL_STATIC_DRAW);
	Texture* groundTexture = textureManager.load("cobblestone");
	scene.addEntity(TexturedEntity(groundTexture, &groundModel, &cubeMaterial, groundEntity));

	// Brass: http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
	//Material cubeMaterial(
	//	glm::vec3(0.329412f, 0.223529f, 0.027451f), // Ambient
	//	glm::vec3(0.780392f, 0.568627f, 0.113725f), // Diffuse
	//	glm::vec3(0.992157f, 0.941176f, 0.807843f), // Specular
	//	27.8974f); // Shine

	// Load Shaders
	fontShader.load("../Testgl/res/shader/text.vert", "../Testgl/res/shader/text.frag");
	scene.load();

	// Capture cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		frameCounter.update(glfwGetTime());

		// Clear
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Lighting
		scene.spotLights[0].rotation = scene.camera.rotation;
		scene.spotLights[0].position = scene.camera.position;
		scene.spotLights[0].updateModelMatrix();

		scene.pointLights[0].position.x = glm::sin(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[0].position.y = glm::cos(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[0].updateModelMatrix();
		scene.pointLights[1].position.x = glm::cos(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[1].position.y = glm::sin(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[1].updateModelMatrix();
		scene.pointLights[2].position.z = glm::sin(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[2].position.y = glm::cos(0.2f * (float)glfwGetTime()) * 3.0f;
		scene.pointLights[2].updateModelMatrix();
		
		// Draw scene
		scene.draw();

		// Draw text
		fontShader.use();
		fontShader.setMat4("projection", glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight));
		glUniform3f(glGetUniformLocation(fontShader.ID, "textColor"), 1.0f, 1.0f, 1.0f);
		fontManager.drawText(std::to_string(frameCounter.fps), 25.0f, 25.0f, 0.5f);
		fontManager.drawText("pos: " + glm::to_string(scene.camera.position), 25.0f, 200.0f, 0.5f);
		fontManager.drawText("rot: " + glm::to_string(scene.camera.rotation), 25.0f, 175.0f, 0.5f);
		fontManager.drawText("up: " + glm::to_string(scene.camera.up), 25.0f, 150.0f, 0.5f);
		fontManager.drawText("right: " + glm::to_string(scene.camera.right), 25.0f, 125.0f, 0.5f);
		fontManager.drawText("front: " + glm::to_string(scene.camera.forward), 25.0f, 100.0f, 0.5f);
		fontManager.drawText("fov: " + std::to_string(scene.camera.fov), 25.0f, 75.0f, 0.5f);

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
		scene.camera.rotateAbsolute(glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(xoffset * MOUSE_SENSITIVITY));
		// Rotate then pitch -> pitch should add to existing pitch
		scene.camera.rotate(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(yoffset * MOUSE_SENSITIVITY));
		
		// Make sure screen doesn't get flipped by clamping pitch
		/*if (camera.rotation.y > 89.0f)
			camera.rotation.y = 89.0f;
		if (camera.rotation.y < -89.0f)
			camera.rotation.y = -89.0f;*/

		scene.camera.updateDirection();
	}
}

void Window::mouseScrolled(double xoffset, double yoffset)
{
	if (scene.camera.fov >= 1.0f && scene.camera.fov <= 120.0f)
		scene.camera.fov -= (float)yoffset;
	if (scene.camera.fov <= 1.0f)
		scene.camera.fov = 1.0f;
	if (scene.camera.fov >= 120.0f)
		scene.camera.fov = 120.0f;
	//camera.rotate(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(yoffset * 5.0f)); // Roll
	scene.camera.updateDirection();
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
		scene.camera.position += cameraMovement * scene.camera.forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene.camera.position -= cameraMovement * scene.camera.forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene.camera.position -= glm::normalize(glm::cross(scene.camera.forward, scene.camera.up)) * cameraMovement;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene.camera.position += glm::normalize(glm::cross(scene.camera.forward, scene.camera.up)) * cameraMovement;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		scene.camera.position += cameraMovement * scene.camera.up;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		scene.camera.position -= cameraMovement * scene.camera.up;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		scene.camera.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		scene.camera.updateDirection();
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
