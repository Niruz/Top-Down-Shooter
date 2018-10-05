#pragma once
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

#include <GL\glew.h>
#include <glfw3.h>

#include <windows.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <stdarg.h> 

// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
// glm::value_ptr
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/glm.hpp> // vec3 normalize reflect dot pow
#include <glm\gtx\vector_angle.hpp>

#include <irrklang/irrKlang.h>

#include "Miner.h"
#include "MinersWife.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "TileMap.h"
#include "ShaderManager.h"
#include "TextureManager.h"
using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

float mHeight = 720.0f;
float mWidth = 1280.0f;
float aspectRatio = mWidth / mHeight;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024] = { false };

bool firstMouse = true;

GLfloat lastX = 640.0f;
GLfloat lastY = 360.0f;
glm::vec3 cameraPos = glm::vec3(0.0f);



static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

/*lastX = xpos;
	lastY = ypos;

	mCamera.processMouseMovement(xoffset, yoffset);*/
}
void updateInput(GLfloat deltaTime)
{
	// Camera controls
/*	if (keys[GLFW_KEY_W])
		mCamera.processKeyBoard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		mCamera.processKeyBoard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		mCamera.processKeyBoard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		mCamera.processKeyBoard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE])
		mCamera.processKeyBoard(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_CONTROL])
		mCamera.processKeyBoard(DOWN, deltaTime);*/
}

int main(void)
{


	//****************************************************//
	//                                                    //
	//               GLFW INITIALIZATION                  //
	//                                                    //
	//****************************************************//
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	/*	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	int major;
	int minor;
	glfwGetVersion(&major, &minor, NULL);

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 720, "Top Down Shooter", NULL, NULL);

	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", glfwGetPrimaryMonitor(), NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.   
	glfwMakeContextCurrent(window);

	//Sets the relevant callbacks 
	//Initialize GLEW  
	glewExperimental = true;
	GLenum err = glewInit();

	//If GLEW hasn't initialized  
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return -1;
	}
	//****************************************************//
	//                                                    //
	//             //GLFW INITIALIZATION                  //
	//                                                    //
	//****************************************************//

	glViewport(0, 0, 1280, 720);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	ISound* hehe = SoundEngine->play2D("Audio/Stay_Closer.wav", GL_TRUE);
	//SoundEngine->isCurrentlyPlaying("Audio/Stay_Closer.wav"))
	//SoundEngine->stopAllSounds();
	//create a miner
	Miner* Bob = new Miner(ent_Miner_Bob, "Bob");

	//create his wife
	MinersWife* Elsa = new MinersWife(ent_Elsa, "Elsa");

	//register them with the entity manager
	EntityMan->registerEntity(Bob);
	EntityMan->registerEntity(Elsa);

	ShaderMan->onInitialize();
	TextureMan->onInitialize();


	TileMap myMap("Levels/test.level");

	myMap.printMap();

	std::vector<Tile*> myPath;
	myMap.GetPath(1, 1, 18, 10, myPath);

	myMap.printPath(myPath);



	TileMap myMap2("Levels/test2.level");

	myMap2.printMap();

	std::vector<Tile*> myPath2;
	myMap2.GetPath(1, 1, 18, 10, myPath2);

	myMap2.printPath(myPath2);



	TileMap myMap3("Levels/test3.level");

	myMap3.printMap();

	std::vector<Tile*> myPath3;
	myMap3.GetPath(1, 1, 18, 10, myPath3);

	myMap3.printPath(myPath3);


	TileMap myMap4("Levels/test4.level");

	myMap4.printMap();

	std::vector<Tile*> myPath4;
	myMap4.GetPath(1, 1, 28, 10, myPath4);

	myMap4.printPath(myPath4);


	TileMap myMap5("Levels/test5.level");

	myMap5.printMap();

	std::vector<Tile*> myPath5;
	myMap5.GetPath(1, 1, 64, 3, myPath5);

	myMap5.printPath(myPath5);


	myPath5.clear();
	myMap5.GetPath(14, 1, 14, 21, myPath5);

	myMap5.printPath(myPath5);
	//run Bob and Elsa through a few Update calls
	for (int i = 0; i<30; ++i)
	{
		Bob->update();
		Elsa->update();

		//dispatch any delayed messages
		MessageMan->dispatchDelayedMessages();

		Sleep(800);
	}

	//tidy up
	delete Bob;
	delete Elsa;
	do
	{
		// Update the input
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		updateInput(deltaTime);




		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);


		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...  
		glfwPollEvents();

	} while (!glfwWindowShouldClose(window));


	ShaderMan->onDeinitialize();
	TextureMan->onDeinitialize();
	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
};
