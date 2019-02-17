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

#include "SoundManager.h"



#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "TileMap.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Camera.h"
#include "MeshFactory.h"
#include "Renderable.h"
#include "Renderer.h"
#include "BatchRenderer.h"
#include "Static_Sprite.h"
#include "Sprite.h"
#include "SimpleTimer.h"
#include "TileLayer.h"
#include "Layer.h"
#include "Group.h"
#include "Label.h"
#include "Font.h"
#include "FontManager.h"
#include "GothicVania.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "rapidxml-1.13\rapidxml.hpp"
#include "rapidxml-1.13\rapidxml_utils.hpp"
#include "TiledMapManager.h"
//ISoundEngine *SoundEngine = createIrrKlangDevice();

float mHeight = 720.0f;
float mWidth = 1280.0f;
float aspectRatio = mWidth / mHeight;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool currentKeyState[1024] = { false };
bool oldKeyState[1024] = { false };
bool keyPressRelease[1024] = { false };
bool oldKeyPressRelease[1024] = { false };
bool currentKeyRepeat[1024] = { false };


bool firstMouse = true;
GLfloat lastX = 640.0f;
GLfloat lastY = 360.0f;

bool mouseMovement = false;

Game* myGame;
int oldPlayerX = -1;
int oldPlayerY = -1;
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
			currentKeyState[key] = true;
		else if (action == GLFW_RELEASE)
		{
			currentKeyRepeat[key] = false;
			currentKeyState[key] = false;
		}
		else if (action == GLFW_REPEAT)
		{
			currentKeyRepeat[key] = true;
		}
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
	mouseMovement = false;

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	if (lastX != xpos || lastY != ypos)
		mouseMovement = true;

	lastX = xpos;
	lastY = ypos;

	myGame->ProcessMouse(lastX, lastY, mouseMovement);
}

void updateInput(GLfloat deltaTime)
{
	//C
	if (currentKeyState[GLFW_KEY_ESCAPE] && !oldKeyState[GLFW_KEY_ESCAPE])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_ESCAPE, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_ESCAPE] = true;
		std::cout << "Escape Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_ESCAPE] && oldKeyState[GLFW_KEY_ESCAPE])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_ESCAPE, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_ESCAPE] = false;
		std::cout << "Escape Released" << std::endl;
	}
	//V
	//C
	if (currentKeyState[GLFW_KEY_C] && !oldKeyState[GLFW_KEY_C])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_C, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_C] = true;
		std::cout << "C Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_C] && oldKeyState[GLFW_KEY_C])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_C, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_C] = false;
		std::cout << "C Released" << std::endl;
	}
	//V
	if (currentKeyState[GLFW_KEY_V] && !oldKeyState[GLFW_KEY_V])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_V, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_V] = true;
		std::cout << "V Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_V] && oldKeyState[GLFW_KEY_V])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_V, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_V] = false;
		std::cout << "V Released" << std::endl;
	}
	//B
	if (currentKeyState[GLFW_KEY_B] && !oldKeyState[GLFW_KEY_B])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_B, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_B] = true;
		std::cout << "B Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_B] && oldKeyState[GLFW_KEY_B])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_B, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_B] = false;
		std::cout << "B Released" << std::endl;
	}
	//T
	if (currentKeyState[GLFW_KEY_T] && !oldKeyState[GLFW_KEY_T])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_T, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_T] = true;
		std::cout << "T Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_T] && oldKeyState[GLFW_KEY_T])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_T, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_T] = false;
		std::cout << "T Released" << std::endl;
	}
	//SPACE
	if (currentKeyState[GLFW_KEY_SPACE] && !oldKeyState[GLFW_KEY_SPACE])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_SPACE, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_SPACE] = true;
		std::cout << "Space Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_SPACE] && oldKeyState[GLFW_KEY_SPACE])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_SPACE, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_SPACE] = false;
		std::cout << "Space Released" << std::endl;
	}
	//E
	if (currentKeyState[GLFW_KEY_E] && !oldKeyState[GLFW_KEY_E])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_E, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_E] = true;
		std::cout << "E Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_E] && oldKeyState[GLFW_KEY_E])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_E, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_E] = false;
		std::cout << "E Released" << std::endl;
	}
	//R
	if (currentKeyState[GLFW_KEY_R] && !oldKeyState[GLFW_KEY_R])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_R, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_R] = true;
		std::cout << "R Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_R] && oldKeyState[GLFW_KEY_R])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_R, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_R] = false;
		std::cout << "R Released" << std::endl;
	}
	//R
	if (currentKeyState[GLFW_KEY_G] && !oldKeyState[GLFW_KEY_G])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_G, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_G] = true;
		std::cout << "G Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_G] && oldKeyState[GLFW_KEY_G])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_G, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_G] = false;
		std::cout << "G Released" << std::endl;
	}
	//Enter
	if (currentKeyState[GLFW_KEY_ENTER] && !oldKeyState[GLFW_KEY_ENTER])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_ENTER, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_ENTER] = true;
		std::cout << "Enter Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_ENTER] && oldKeyState[GLFW_KEY_ENTER])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_ENTER, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_ENTER] = false;
		std::cout << "Enter Released" << std::endl;
	}
	//Q
	/*if (currentKeyState[GLFW_KEY_Q] && !oldKeyState[GLFW_KEY_Q])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_Q, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_Q] = true;
		std::cout << "Q Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_Q] && oldKeyState[GLFW_KEY_Q])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_Q, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_Q] = false;
		std::cout << "Q Released" << std::endl;
	}*/

	//This will double the initial press key by one
	if (currentKeyState[GLFW_KEY_A] && !oldKeyState[GLFW_KEY_A])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_A, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_A] = true;
		std::cout << "A Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_A] && oldKeyState[GLFW_KEY_A])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_A, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_A] = false;
		std::cout << "A Released" << std::endl;
	}
	//D
	if (currentKeyState[GLFW_KEY_D] && !oldKeyState[GLFW_KEY_D])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_D, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_D] = true;
		std::cout << "D Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_D] && oldKeyState[GLFW_KEY_D])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_D, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_D] = false;
		std::cout << "D Released" << std::endl;
	}

//	if (currentKeyState[GLFW_KEY_G])
//		myGame->ProcessKeyBoard(GLFW_KEY_G, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_W])
		myGame->ProcessKeyBoard(GLFW_KEY_W, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_S])
		myGame->ProcessKeyBoard(GLFW_KEY_S, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_A])
		myGame->ProcessKeyBoard(GLFW_KEY_A, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_D])
		myGame->ProcessKeyBoard(GLFW_KEY_D, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_Q])
		myGame->ProcessKeyBoard(GLFW_KEY_Q, deltaTime, GLFW_PRESS);
	if (currentKeyRepeat[GLFW_KEY_V])
		myGame->ProcessKeyBoard(GLFW_KEY_V, deltaTime, GLFW_REPEAT);
	/*if (currentKeyState[GLFW_KEY_1])
		myGame->ProcessKeyBoard(GLFW_KEY_1, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_2])
		myGame->ProcessKeyBoard(GLFW_KEY_2, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_3])
		myGame->ProcessKeyBoard(GLFW_KEY_3, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_4])
		myGame->ProcessKeyBoard(GLFW_KEY_4, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_5])
		myGame->ProcessKeyBoard(GLFW_KEY_5, deltaTime, GLFW_PRESS);
	if (currentKeyState[GLFW_KEY_6])
		myGame->ProcessKeyBoard(GLFW_KEY_6, deltaTime, GLFW_PRESS);*/
}
glm::vec2 convertRange()
{
	return glm::vec2(1, 1);
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
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*ISound* hehe = SoundEngine->play2D("Audio/Stay_Closer.wav", GL_TRUE);
	SoundEngine->isCurrentlyPlaying("Audio/Stay_Closer.wav");
	SoundEngine->stopAllSounds();
	*/


	ShaderMan->onInitialize();
	TextureMan->onInitialize();
	FontMan->onInitialize();
	SoundMan->OnInitialize();
	TiledMan->onInitialize();
	ISound* hehe = SoundMan->GetSoundEngine()->play2D("Audio/Stay_Closer.wav", GL_TRUE);
	SoundMan->GetSoundEngine()->isCurrentlyPlaying("Audio/Stay_Closer.wav");
	SoundMan->GetSoundEngine()->stopAllSounds();

	//myGame = new Pacman();
	//myGame = new Shooter();
	myGame = new GothicVania();
	myGame->Initialize();
	//SoundEngine->play2D("Audio/Stay_Closer.wav", GL_TRUE);
	do
	{
		// Update the input
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		updateInput(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


		myGame->Run();

		//std::cout << glGetError() << std::endl;
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...  
		glfwPollEvents();

	} while (!glfwWindowShouldClose(window));


	ShaderMan->onDeinitialize();
	TextureMan->onDeinitialize();
	FontMan->onDeinitialize();
	SoundMan->OnDeinitialize();
	TiledMan->onDeinitialize();
	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
};