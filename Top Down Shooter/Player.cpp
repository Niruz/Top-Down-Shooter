#include "Player.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "ShaderManager.h"
#include <iostream>
# define M_PI3           3.14159265358979323846  /* pi */

Player::Player() : translationMatrix(1.0f),
rotationMatrix(1.0f), modelMatrix(1.0f), mAngle(0.0f)
{
	mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
}
Player::~Player()
{

}
void Player::updatePosition(const glm::vec3& position)
{
	mPosition += position;
}
void Player::setPosition(const glm::vec3& pos)
{
	mPosition = pos;
	translationMatrix = glm::translate(translationMatrix, mPosition);
}
void Player::setDirection(const glm::vec2& direction)
{
	float angle = atan2(direction.y, direction.x);// *(180.0f / M_PI3);
	float degreesRadians = (M_PI3 / 180)*90.0f;

	mAngle = angle - degreesRadians;

	std::cout << "angle: " << mAngle << std::endl;
}
void Player::render(const Camera& camera)
{
	rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, mAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, mPosition);

	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(16, 16, 16));

	modelMatrix =  camera.mTranslationMatrix* translationMatrix *rotationMatrix *scaleMatrix;
	//modelMatrix = rotationMatrix;

	ShaderMan->setUniformMatrix4fv("modelMatrix", 1, GL_FALSE, modelMatrix);

	mTexture->bind();

	mMesh->render();


	mTexture->unbind();
}

void Player::processKeyBoard(camMovement direction, GLfloat deltaTime)
{
	GLfloat velocity = 100.5f * deltaTime;

	if (direction == FORWARD)
		mPosition += glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
	else if (direction == BACKWARD)
		mPosition -= glm::vec3(0.0f, 1.0f, 0.0f)*velocity;
	else if (direction == RIGHT)
		mPosition += glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
	else if (direction == LEFT)
		mPosition -= glm::vec3(1.0f, 0.0f, 0.0f)*velocity;
	/*	else if (direction == UP)
	mPosition += mWorldUp*velocity;
	else if (direction == DOWN)
	mPosition -= mWorldUp*velocity;*/
}