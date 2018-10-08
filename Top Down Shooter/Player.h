#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

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

	void render(const Camera& camera);

	void updatePosition(const glm::vec3& pos);
	void setPosition(const glm::vec3& pos);
	void setDirection(const glm::vec2& direction);
	void processKeyBoard(camMovement direction, GLfloat deltaTime);

	glm::vec3 mPosition;
	glm::mat4 translationMatrix;
	glm::mat4 rotationMatrix;
	glm::mat4 modelMatrix;

	float mAngle;
};
