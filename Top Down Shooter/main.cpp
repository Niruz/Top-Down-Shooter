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

#include "Miner.h"
#include "MinersWife.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "TileMap.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Player.h"
#include "Camera.h"
#include "MeshFactory.h"
#include "SimpleObject.h"
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
#include "Pacman.h"
#include "Shooter.h"
#include "GothicVania.h"


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
glm::vec2 playerPos = glm::vec2(0.0f, 0.0f);
GLfloat lastX = 640.0f;
GLfloat lastY = 360.0f;
float distanceToMouse = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f);
bool mouseMovement = false;
Camera* mCamera;
Player mPlayer;
Mesh* mMesh;
Texture* mTexture;
Mesh* mMesh2;
Mesh* mMesh3;
Texture* mTexture3;
Texture* mTexture2;
Texture* mTexture4;
Texture* mTexture5;
Texture* mTexture6;
Texture* mTexture7;
Texture* mTexture8;
Texture* mTexture9;
Texture* mTexture10;
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

//	mCamera->setScreenPosition(glm::vec2(lastX, lastY));
	myGame->ProcessMouse(lastX, lastY, mouseMovement);

	//	mCamera.processMouseMovement(xoffset, yoffset);
}
/*
void updateInput(GLfloat deltaTime, TileMap& map)
{
	if (keys[GLFW_KEY_W])
		myPacman.ProcessKeyBoard(0, deltaTime);
		//mPlayer.processKeyBoard(FORWARD, deltaTime,map);
	if (keys[GLFW_KEY_S])
		myPacman.ProcessKeyBoard(1, deltaTime);
		//mPlayer.processKeyBoard(BACKWARD, deltaTime, map);
	if (keys[GLFW_KEY_A])
		myPacman.ProcessKeyBoard(2, deltaTime);
		//mPlayer.processKeyBoard(LEFT, deltaTime, map);
	if (keys[GLFW_KEY_D])
		myPacman.ProcessKeyBoard(3, deltaTime);
		//mPlayer.processKeyBoard(RIGHT, deltaTime, map);
	if (keys[GLFW_KEY_SPACE])
		mPlayer.processKeyBoard(UP, deltaTime, map);
	if (keys[GLFW_KEY_LEFT_CONTROL])
		mPlayer.processKeyBoard(DOWN, deltaTime, map);
}*/
void updateInput(GLfloat deltaTime)
{
	/*//W
	if (currentKeyState[GLFW_KEY_W] && !oldKeyState[GLFW_KEY_W]) 
	{
		myGame->ProcessKeyBoard(GLFW_KEY_W, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_W] = true;
		std::cout << "W Pressed" << std::endl;
	}
	else if(!currentKeyState[GLFW_KEY_W] && oldKeyState[GLFW_KEY_W])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_W, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_W] = false;
		std::cout << "W Released" << std::endl;
	}
	//S
	if (currentKeyState[GLFW_KEY_S] && !oldKeyState[GLFW_KEY_S])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_S, deltaTime, GLFW_PRESS);
		oldKeyState[GLFW_KEY_S] = true;
		std::cout << "S Pressed" << std::endl;
	}
	else if (!currentKeyState[GLFW_KEY_S] && oldKeyState[GLFW_KEY_S])
	{
		myGame->ProcessKeyBoard(GLFW_KEY_S, deltaTime, GLFW_RELEASE);
		oldKeyState[GLFW_KEY_S] = false;
		std::cout << "S Released" << std::endl;
	}
	//A
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
	}*/
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
	glm::vec2 startRange(-320.0f, 160);
	glm::vec2 endRange(288.0f, -192.0f);
	
	glm::vec2 range = endRange - startRange;

	glm::vec2 test = glm::vec2(mPlayer.mPosition.x / range.x, mPlayer.mPosition.y / range.y);

	glm::vec2 testTilePos;
	testTilePos.x = glm::floor(test.x);
	testTilePos.y = glm::floor(test.y);

	glm::vec2 test2;
	test.x = mPlayer.mPosition.x / 32.0f;
	test.x = mPlayer.mPosition.y / 32.0f;
	int shit = 5;

	float a = -320.0f;
	float b = 288.0f;
	float c = 0;
	float d = 21;


	float a2 = 160;
	float b2 = -192;
	float c2 = 0;
	float d2 = 11;
	float testNew = ((mPlayer.mPosition.x - a) * ((d - c) / (b - a))) + c;
	float testNew2 = ((mPlayer.mPosition.y - a2) * ((d2 - c2) / (b2 - a2))) + c2;

	float roundX = round(testNew);
	float roundY = round(testNew2);

	if (roundX != oldPlayerX)
		oldPlayerX = roundX;
	if (roundY != oldPlayerY)
		oldPlayerY = roundY;

	return glm::vec2(1, 1);
}

#ifdef TESTMAIN
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ISound* hehe = SoundEngine->play2D("Audio/Stay_Closer.wav", GL_TRUE);
	SoundEngine->isCurrentlyPlaying("Audio/Stay_Closer.wav");
	SoundEngine->stopAllSounds();

	//if (hehe != NULL) //check to see if there's a sound playing
	//	hehe->drop(); //drop the sound
	//create a miner
	Miner* Bob = new Miner(ent_Miner_Bob, "Bob");

	//create his wife
	MinersWife* Elsa = new MinersWife(ent_Elsa, "Elsa");

	//register them with the entity manager
	EntityMan->registerEntity(Bob);
	EntityMan->registerEntity(Elsa);

	ShaderMan->onInitialize();
	TextureMan->onInitialize();
	FontMan->onInitialize();


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

	std::vector<Tile*> map = myMap3.GetMap();


	/*TileMap myMap4("Levels/test4.level");

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

	myMap5.printPath(myPath5);*/


	//run Bob and Elsa through a few Update calls
	/*for (int i = 0; i<30; ++i)
	{
		Bob->update();
		Elsa->update();

		//dispatch any delayed messages
		MessageMan->dispatchDelayedMessages();

		Sleep(800);
	}*/

	//tidy up
	delete Bob;
	delete Elsa;

	mMesh = MeshFactory::createCube();
	mMesh2 = MeshFactory::createCube();
	mMesh3 = MeshFactory::createCube();
	Texture* myTexture = TextureMan->GetTexture("player");

	mTexture = TextureMan->GetTexture("cursor");
	mTexture2 = TextureMan->GetTexture("floor");
	mTexture3 = TextureMan->GetTexture("wall");
	mTexture4 = TextureMan->GetTexture("floor2");
	mTexture5 = TextureMan->GetTexture("1");
	mTexture6 = TextureMan->GetTexture("2");
	mTexture7 = TextureMan->GetTexture("3");
	mTexture8 = TextureMan->GetTexture("4");
	mTexture9 = TextureMan->GetTexture("5");
	mTexture10 = TextureMan->GetTexture("6");
	//glm::mat4 ortho = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
	//1280 720
	//glm::mat4 ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);





	mCamera.setScreenPosition(glm::vec2(lastX, lastY));
	mCamera.setProjectionMatrix(ortho);
	mCamera.setWidth(mWidth);
	mCamera.setHeight(mHeight);

	mPlayer.mMesh = mMesh;
	mPlayer.mTexture = mTexture;
	mPlayer.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	Renderer myRenderer; 
	BatchRenderer myBatchRenderer;
	Renderable* myRenderable = new StaticSprite(glm::vec4(0.0f,0.0f,0.0f,1), glm::vec2(32,32), glm::vec4(1.0f,0.0f,1.0f,1.0f));
	Renderable* myRenderable2 = new StaticSprite(glm::vec4(32.0f, 0.0f, 0.0f,1), glm::vec2(32, 32), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	Renderable* myRenderable3 = new Sprite(glm::vec4(0.0f, 0.0f, 0.0f,1), glm::vec2(32, 32), glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Renderable* myRenderable4 = new Sprite(glm::vec4(32.0f, 0.0f, 0.0f,1), glm::vec2(32, 32), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	
	std::vector<StaticSprite*> staticSprites;
	std::vector<Sprite*> sprites;
	
	/*for (int i = 0; i < map.size(); i++) 
	{
		glm::vec3 position = glm::vec3(map[i]->myWorldPosition,0.0f);
		glm::vec4 color;
		glm::vec2 size = glm::vec2(32, 32);
		map[i]->myIsBlockingFlag ? color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f) : color = glm::vec4(0.0, 0.0f, 1.0f, 1.0f);
		sprites.push_back(new Sprite(position, size, color));
	}
	for (int i = 0; i < map.size(); i++)
	{
		glm::vec3 position = glm::vec3(map[i]->myWorldPosition, 0.0f);
		glm::vec4 color;
		glm::vec2 size = glm::vec2(32, 32);
		map[i]->myIsBlockingFlag ? color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f) : color = glm::vec4(0.0, 0.0f, 1.0f, 1.0f);
		staticSprites.push_back(new StaticSprite(position, size, color));
	}
	*/
//	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	TileLayer layer(ShaderMan->getShader(SIMPLE_FORWARD_SHADER));
	TileLayer layer2(ShaderMan->getShader(SIMPLE_MENU_SHADER));
	TileLayer mapLayer(ShaderMan->getShader(SIMPLE_FORWARD_SHADER));
	//THIS ONE BELOW IS FOR THE 50K SPRITES
	/*for(float y = -360; y < 360.0f; y+=4.0f)
	{
		for(float x = -640.0f; x < 640.0f; x+=4.0f)
		{
			//sprites.push_back(new Sprite(glm::vec3(x,y,0), glm::vec2(3.5f,3.5f), glm::vec4(rand()%1000/	1000.0f,0,1,1)));
			layer.Add(new Sprite(glm::vec3(x, y, 0), glm::vec2(3.5f, 3.5f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}*/
	Texture* textures[] = {
		mTexture ,
		mTexture2 ,
		mTexture3,
		mTexture4,
		mTexture5,
		mTexture6,
		mTexture7,
		mTexture8,
		mTexture9,
		mTexture10
	};

	glm::vec2 atlasPos[] = 
	{
		glm::vec2(0, 15), glm::vec2(1, 15), glm::vec2(2, 15), glm::vec2(3, 15), glm::vec2(4, 15),
		glm::vec2(5, 15), glm::vec2(6, 15), glm::vec2(7, 15), glm::vec2(8, 15), glm::vec2(9, 15),
		glm::vec2(10, 15), glm::vec2(11, 15), glm::vec2(12, 15), glm::vec2(13, 15), glm::vec2(14, 15),
		glm::vec2(15, 15), glm::vec2(0, 14), glm::vec2(1, 14), glm::vec2(2, 14), glm::vec2(3, 14),
		glm::vec2(4, 14), glm::vec2(5, 14), glm::vec2(6, 14), glm::vec2(7, 14), glm::vec2(8, 14),
		glm::vec2(9, 14), glm::vec2(10, 14), glm::vec2(11, 14), glm::vec2(12, 14), glm::vec2(13, 14),
		glm::vec2(14, 14), glm::vec2(15, 14), glm::vec2(0, 13), glm::vec2(1, 13), glm::vec2(2, 13), glm::vec2(3, 13)
	};
	for (float y = -360; y < 360.0f; y += 24.0f)
	{
		for (float x = -640.0f; x < 640.0f; x += 24.0f)
		{
			//sprites.push_back(new Sprite(glm::vec3(x,y,0), glm::vec2(3.5f,3.5f), glm::vec4(rand()%1000/	1000.0f,0,1,1)));
			//layer.Add(new Sprite(glm::vec3(x, y, 0), glm::vec2(15.5f, 15.5f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			
			/*if(rand() % 4 == 0)
				layer.Add(new Sprite(glm::vec4(x, y, 0,1), glm::vec2(19.5f, 19.5f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				layer.Add(new Sprite(glm::vec4(x, y, 0,1), glm::vec2(19.5f, 19.5f), textures[rand()%10]));
			*/
		/*	if (rand() % 4 == 0)
				layer.Add(new Sprite(glm::vec4(x, y, 0, 1), glm::vec2(19.5f, 19.5f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else*/
			layer.Add(new Sprite(glm::vec4(x, y, 0, 1), glm::vec2(19.5f, 19.5f), TextureMan->GetTexture("atlas"), atlasPos[rand()%35]));
			//layer.Add(new Sprite(glm::vec4(x, y, 0,1), glm::vec2(19.5f, 19.5f), TextureMan->GetTexture(std::to_string(rand() % 35))));

		/*	if (y > 0)
			{
				layer.Add(new Sprite(glm::vec3(x, y, 0), glm::vec2(15.5f, 15.5f), mTexture3));
			}
			else
			{
				layer.Add(new Sprite(glm::vec3(x, y, 0), glm::vec2(15.5f, 15.5f), mTexture4));
			}*/
		}
	}
	/*float rowX = -640;
	float rowY = -360;
	for(int i = 0; i < 5; i++)
	{
		layer.Add(new Sprite(glm::vec3(rowX, rowY, 0), glm::vec2(19.5f, 19.5f), TextureMan->GetTexture(std::to_string(i))));
		rowX += 24.0f;
	}*/
	/*for (float y = -360; y < 360.0f; y += 9.0f)
	{
		for (float x = -640.0f; x < 640.0f; x += 9.0f)
		{
			staticSprites.push_back(new StaticSprite(glm::vec3(x, y, 0), glm::vec2(8.0f, 8.0f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}*/

	GLint max_combined_texture_image_units;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_units);
	//layer.Add(new Sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(32, 32), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	//layer.Add(new Sprite(glm::vec3(32.0f, 0.0f, 0.0f), glm::vec2(32, 32), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));
	glm::mat4 trmat =  glm::translate(glm::mat4(1.0f), glm::vec3(32.0f, 0.0f, 0.1f)) * glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f)) ;
	Group* group = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	//Group* group = new Group(trmat);
	Sprite* atlasTest = new Sprite(glm::vec4(0.0f, 0.0f, 0.1f, 1), glm::vec2(512, 512), TextureMan->GetTexture("atlas"));
	atlasTest->SetUVs(0, 15);
	group->Add(atlasTest);

	/*Group* button = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(16,16,0)));
	//Group* button = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(16, 16, 0))* glm::rotate(glm::mat4(1.0f), -45.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	button->Add(new Sprite(glm::vec3(0.0f,0.0f, 0.2f), glm::vec2(32, 32), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));


	button->Add(new Sprite(glm::vec3(8.0f, 8.0f, 0.21f), glm::vec2(16, 16), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	group->Add(button);*/
	layer2.Add(group);

	layer.Add(group);

	//Font* font = new Font("DefaultFont","Fonts/SourceSansPro-Light.ttf",32);
	Font* font = FontMan->GetFont("DefaultFont32");
	Group* fpsGroup = new Group(glm::translate(glm::mat4(1.0f), glm::vec3(-580,340,0.8)));
	//Label* fpsLabel = new Label("", glm::vec3(-640, 336, 1), glm::vec4(0, 0, 1, 1));

	//Label* fpsLabel = new Label("", glm::vec3(0, 0, 0), font, glm::vec4(0, 1, 0, 1));
	Label* fpsLabel = new Label("", glm::vec4(-55, -10, 0,1), "DefaultFont32", glm::vec4(0, 1, 0, 1));
	//layer.Add(new Label("Hello!", glm::vec3(0, 0, 1), glm::vec4(0, 0, 1, 1)));
	
	fpsGroup->Add(new Sprite(glm::vec4(0, 0, -0.1,1), glm::vec2(120.5f, 40.5f), glm::vec4(0.2f, 0.2f, 0.2f, 0.9)));
	fpsGroup->Add(fpsLabel);
	layer.Add(fpsGroup);
//	GLint texIDS[] = { 0, 1, 2,3,4,5,6,7,8,9,10,11,12,13,14,15/*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30*/};
	/*Shader* simpleShader = ShaderMan->getShader(SIMPLE_FORWARD_SHADER);
	simpleShader->bind();
	simpleShader->setUniform1iv("textureArray", texIDS, 10);
	simpleShader->unbind();*/
	/*ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
	ShaderMan->setUniform1iv("textureArray[0]", texIDS, 16);
	ShaderMan->unbindShader();*/
	//layer2.Add(new Sprite(glm::vec3(32.0f, 0.0f, 0.1f), glm::vec2(64, 64), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f)));
	//layer2.Add(new Sprite(glm::vec3(16.0f, 16.0f, 0.1f), glm::vec2(16, 16), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
	int fps = 0;
	double lastTime = Clock->GetCurrentTime();

	
	myPacman.Initialize();
	do
	{
		// Update the input
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		updateInput(deltaTime,myMap3);
		fps++;
		double currentTime = Clock->GetCurrentTime();
		if ( currentTime - lastTime >= 1.0)
		{
			std::cout << "fps: " << fps << std::endl;
			fpsLabel->myText = "fps: " + std::to_string(fps);
			lastTime = currentTime;
			fps = 0;
		}


		//myRenderable3->SetPosition(glm::vec3(mCamera.mouseScreenToWorld(glm::vec2(lastX, lastY)),0.0f));
		//myRenderable2->SetPosition(glm::vec3(mCamera.mouseScreenToWorld(glm::vec2(lastX, lastY)), 0.0f));

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		//glClearColor(0.0f, 0.8f, 0.8f, 1.0f);
		//glClearColor(0.5f, 0.5f, 0.50f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
		ShaderMan->setUniform2fv("lightPos", 1, mCamera.mouseScreenToWorld(glm::vec2(lastX, lastY)));
		ShaderMan->unbindShader();
		ShaderMan->bindShader(SIMPLE_MENU_SHADER);
		ShaderMan->setUniform2fv("lightPos", 1, mCamera.mouseScreenToWorld(glm::vec2(lastX, lastY)));
		ShaderMan->unbindShader();

	/*	myRenderer.Submit(myRenderable);
		myRenderer.Submit(myRenderable2);
		//for (StaticSprite* sprite : staticSprites)
		//	myRenderer.Submit(sprite);

		myTexture->bind();
		myRenderer.Flush();
		myTexture->unbind();
		*/
	//	myTexture->bind();


		myPacman.Run();
		//THIS IS THE ONE TO UNCOMMENT
		//layer.Render();



	//	myTexture->unbind();
		//layer2.Render();

	/*	myBatchRenderer.Begin();
		//myBatchRenderer.Submit(myRenderable3);
		//myBatchRenderer.Submit(myRenderable4);
		for (Sprite* sprite : sprites)
			myBatchRenderer.Submit(sprite);
		myBatchRenderer.End();
		myBatchRenderer.Flush();*/
		
		/*
		ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
		float lerp = 0.1f;
		glm::vec3 position = mCamera.getPosition();
		position.x += (mPlayer.mPosition.x - position.x) * lerp * deltaTime;
		position.y += (mPlayer.mPosition.y - position.y) * lerp * deltaTime;

		mCamera.setPosition(-mPlayer.mPosition);
		mPlayer.setDirection(mCamera.getPlayerDirection(mPlayer.mPosition));

		ShaderMan->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, mCamera.getProjectionMatrix());

		mPlayer.render(mCamera);


		glm::mat4 translationMatrix2 = glm::mat4(1.0f);

		glm::vec2 mouseScreenWorld = mCamera.mouseScreenToWorld(glm::vec2(lastX, lastY));

		glm::vec2 testTilePos;
		
		testTilePos.x = glm::floor(mPlayer.mPosition.x / 32.0f);
		testTilePos.y = glm::floor(mPlayer.mPosition.y / 32.0f);


		glm::mat4 tran = glm::mat4(1.0f);
		tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));

		glm::mat4 scal = glm::mat4(1.0f);
		scal = glm::scale(scal, glm::vec3(16, 16, 16));
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, tran * scal);
		mTexture4->bind();

		mMesh->render();

		mTexture4->unbind();



		if (mouseMovement)
			translationMatrix2 = glm::translate(translationMatrix2, glm::vec3(mouseScreenWorld, 0.0f));
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translationMatrix2);

		myMap3.setPlayerTile(mPlayer.mPosition.x, mPlayer.mPosition.y);
		float startX = -32.0f * 10.0f;
		float startY = 32.0f * 6;
		for(int i = 0; i < map.size(); i++)
		{
			if(i % 20 == 0 )
			{
				startY -= 32.0f;
				startX = -32.0f*10.0f;
			}

			if (i == 239)
				int shitterooo = 5;
			if(map[i]->isPlayerOnTile)
			{
				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
				mTexture4->bind();
				mMesh->render();
				mTexture4->unbind();
			}
			else if(map[i]->myIsBlockingFlag)
			{
				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix );
				mTexture3->bind();
				mMesh->render();

				mTexture3->unbind();
			}
			else
			{

				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
				mTexture2->bind();
				mMesh->render();
				mTexture2->unbind();
			}
			startX += 32.0f;
		}
		std::cout << glGetError() << std::endl;
		ShaderMan->unbindShader();
		*/

		//std::cout << glGetError() << std::endl;
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...  
		glfwPollEvents();

	} while (!glfwWindowShouldClose(window));


	ShaderMan->onDeinitialize();
	TextureMan->onDeinitialize();
	FontMan->onDeinitialize();
	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
};
#endif
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
	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
};