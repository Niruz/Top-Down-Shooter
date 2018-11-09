#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

class TileMap;
class Mesh;
class Texture;
class Group;

enum camMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Player
{
	Player();
	~Player();


	Mesh* mMesh;
	Texture* mTexture;
	Group* mySprite;

	void render(const Camera& camera);
	void UpdateTransformationMatrix(const Camera& camera);

	void updatePosition(const glm::vec3& pos);
	void setPosition(const glm::vec3& pos);
	void setDirection(const glm::vec2& direction);
	void processKeyBoard(camMovement direction, GLfloat deltaTime, TileMap& map);
	float map(float s, float a1, float a2, float b1, float b2);
	glm::vec3 mPosition;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 modelMatrix;

	float mAngle;
};
