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

#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Player.h"
#include "Camera.h"
#include "MeshFactory.h"
#include "SimpleObject.h"
using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

float mHeight = 720.0f;
float mWidth = 1280.0f;
float aspectRatio = mWidth / mHeight;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool keys[1024] = { false };

bool firstMouse = true;
glm::vec2 playerPos = glm::vec2(0.0f, 0.0f);
GLfloat lastX = 640.0f;
GLfloat lastY = 360.0f;
float distanceToMouse = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f);
bool mouseMovement = false;
Camera mCamera;
Player mPlayer;
SimpleObject mSimpleObjects[3];
Mesh* mMesh;
Texture* mTexture;
Mesh* mMesh2;
Mesh* mMesh3;
Texture* mTexture3;
Texture* mTexture2;
Texture* mTexture4;

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
	mouseMovement = false;

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	if (lastX != xpos || lastY != ypos)
		mouseMovement = true;

	lastX = xpos;
	lastY = ypos;

	mCamera.setScreenPosition(glm::vec2(lastX, lastY));

	//	mCamera.processMouseMovement(xoffset, yoffset);
}

void updateInput(GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
		mPlayer.processKeyBoard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		mPlayer.processKeyBoard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		mPlayer.processKeyBoard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		mPlayer.processKeyBoard(RIGHT, deltaTime);
	if (keys[GLFW_KEY_SPACE])
		mPlayer.processKeyBoard(UP, deltaTime);
	if (keys[GLFW_KEY_LEFT_CONTROL])
		mPlayer.processKeyBoard(DOWN, deltaTime);
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

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,  //bottom left
		 0.5f, -0.5f, 0.0f,  //bottom right
		-0.5f,  0.5f, 0.0f,  //top left
	     0.5f,  0.5f, 0.0f //top right

	};

	GLfloat texCoords[] = 
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};

	GLuint indices[] =
	{
		0,1,3,
		0,3,2
	};

	Buffer* buffy = new Buffer(vertices, 4 * 3, 3);
	Buffer* texBuffy = new Buffer(texCoords, 4 * 2, 2);
	
	VertexArray* va = new VertexArray();
	va->addBuffer(buffy, 0);
	va->addBuffer(texBuffy, 1);
	IndexBuffer* ib = new IndexBuffer(indices, 6);



	mMesh = MeshFactory::createCube();
	mMesh2 = MeshFactory::createCube();
	mMesh3 = MeshFactory::createCube();
	Texture* myTexture = TextureMan->GetTexture("wall");

	mTexture = TextureMan->GetTexture("cursor");
	mTexture2 = TextureMan->GetTexture("floor");
	mTexture3 = TextureMan->GetTexture("wall");
	mTexture4 = TextureMan->GetTexture("floor2");
	//glm::mat4 ortho = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f);
	//1280 720
	//glm::mat4 ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);

	mSimpleObjects[0].mTexture = mTexture3;
	mSimpleObjects[0].mMesh = mMesh3;
	mSimpleObjects[0].setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	mSimpleObjects[1].mTexture = mTexture3;
	mSimpleObjects[1].mMesh = mMesh3;
	mSimpleObjects[1].setPosition(glm::vec3(32.0f, -32.0f, 0.0f));
	mSimpleObjects[2].mTexture = mTexture3;
	mSimpleObjects[2].mMesh = mMesh3;
	mSimpleObjects[2].setPosition(glm::vec3(64.0f, -64.0f, 0.0f));




	mCamera.setScreenPosition(glm::vec2(lastX, lastY));
	mCamera.setProjectionMatrix(ortho);
	mCamera.setWidth(mWidth);
	mCamera.setHeight(mHeight);

	mPlayer.mMesh = mMesh;
	mPlayer.mTexture = mTexture;
	mPlayer.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	do
	{
		// Update the input
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		updateInput(deltaTime);




		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

		/*ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
		myTexture->bind();
		ShaderMan->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, ortho);
		va->bind();
		ib->bind();
		glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
		ib->unbind();
		va->unbind();
		myTexture->unbind();
		ShaderMan->unbindShader();
		*/

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

	//	myMap3.GetTile2(testTilePos.x, testTilePos.y)->isPlayerOnTile = true;

		glm::mat4 tran = glm::mat4(1.0f);
		tran = glm::translate(tran, glm::vec3(mouseScreenWorld.x, mouseScreenWorld.y, 0.0f));

		glm::mat4 scal = glm::mat4(1.0f);
		scal = glm::scale(scal, glm::vec3(16, 16, 16));
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, tran /** mCamera.mTranslationMatrix*/ * scal);
		mTexture4->bind();

		mMesh->render();

		mTexture4->unbind();



		if (mouseMovement)
			translationMatrix2 = glm::translate(translationMatrix2, glm::vec3(mouseScreenWorld, 0.0f));
		ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translationMatrix2);

		myMap3.setPlayerTile(mPlayer.mPosition.x, mPlayer.mPosition.y);
		//convertRange();
		//myMap3.GetTile2(oldPlayerX, oldPlayerY)->isPlayerOnTile = true;
		float startX = -32.0f * 10.0f;
		float startY = 32.0f * 6;
		for(int i = 0; i < map.size(); i++)
		//for(int i = map.size() - 1; i>= 0; i-- )
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
				/*glm::mat4 translMat = glm::mat4(1.0f);
				translMat = glm::translate(translMat, glm::vec3(startX, startY, 0.0f));

				glm::mat4 scaleMat = glm::mat4(1.0f);
				scaleMat = glm::scale(scaleMat, glm::vec3(16, 16, 16));*/
				//ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translMat * mCamera.mTranslationMatrix * scaleMat);
				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
				mTexture4->bind();

				mMesh->render();

				mTexture4->unbind();
			}
			else if(map[i]->myIsBlockingFlag)
			{
				//ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translMat * mCamera.mTranslationMatrix * scaleMat);
				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix );
				mTexture3->bind();

				mMesh->render();

				mTexture3->unbind();
			}
			else
			{
				/*glm::mat4 translMat = glm::mat4(1.0f);
				glm::vec2 tilePos = map[i]->myWorldPosition;
				translMat = glm::translate(translMat, glm::vec3(tilePos.x, tilePos.y, 0.0f));
				//translMat = glm::translate(translMat, glm::vec3(startX, startY, 0.0f));

				glm::mat4 scaleMat = glm::mat4(1.0f);
				scaleMat = glm::scale(scaleMat, glm::vec3(16, 16, 16));*/
				ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, mCamera.mTranslationMatrix * map[i]->myModelMatrix);
				//ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, translMat * mCamera.mTranslationMatrix * scaleMat);
				mTexture2->bind();

				mMesh->render();

				mTexture2->unbind();
			}
			startX += 32.0f;
		}

		/*for (int i = 0; i < 3; ++i)
		{
			mSimpleObjects[i].render(mCamera);
		}*/





		std::cout << glGetError() << std::endl;


		ShaderMan->unbindShader();

		//std::cout << gluErrorString(glGetError()) << std::endl;

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
