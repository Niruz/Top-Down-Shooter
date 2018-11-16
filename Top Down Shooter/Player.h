#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

class TileMap;
class Mesh;
class Texture;
class Group;
class HeroSprite;

enum camMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum StateTest
{
	RUNNING,
	IDLE,
	CROUCH,
	ATTACKING
};

//Test to see how complex the states will be

struct Player
{
	Player();
	~Player();


	Mesh* mMesh;
	Texture* mTexture;
	Group* mySprite;
	HeroSprite* myAnimatedSprite;

	void render(const Camera& camera);
	void UpdateTransformationMatrix(const Camera& camera);
	void Update();
	void updatePosition(const glm::vec3& pos);
	void setPosition(const glm::vec3& pos);
	void setDirection(const glm::vec2& direction);
	void processKeyBoard(int key, GLfloat deltaTime, int action);
	float map(float s, float a1, float a2, float b1, float b2);
	void SetAnimation(const std::string& name);
	glm::vec3 mPosition;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 modelMatrix;

	glm::vec3 myDirection;


	float myPosXDirection;
	float myPosYDirection;
	float myNegXDirection;
	float myNegYDirection;

	void HandleMovement();

	float mAngle;

	int currentKeyInput;

	TileMap* myTileMap;

	StateTest myState;
};
