#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
Camera::Camera()
{
	mTranslationMatrix = glm::mat4(1.0f);
	mProjectionMatrix = glm::mat4(1.0f);
	mInverseProjectionMatrix = glm::mat4(1.0f);
}
Camera::~Camera()
{

}
void Camera::setPosition(const glm::vec3& position)
{
	mPosition = position;
	mTranslationMatrix = glm::mat4(1.0f);
	mTranslationMatrix = glm::translate(mTranslationMatrix, mPosition);
}
void Camera::setScreenPosition(const glm::vec2& pos)
{
	screenPosition = pos;
}
glm::vec2 Camera::getPlayerDirection(const glm::vec3& pos)
{
	glm::vec4 realPos = mProjectionMatrix * /*mTranslationMatrix */ glm::vec4(pos, 1.0f);

	glm::vec2 mouseToWorld = mouseScreenToWorld(screenPosition);


	glm::vec2 direction = mouseToWorld - glm::vec2(0.0f, 0.0f);
	//	if ((direction.x != 0) && (direction.y == 0))
	//	direction = glm::normalize(direction);

	return direction;

	/*glm::vec4 realPos = ortho * translationMatrix * glm::vec4(playerPos, 0.0f, 1.0f);

	glm::vec2 test = mCamera.mouseScreenToWorld(lastX, lastY);
	std::cout << "x: " << test.x << " y: " << test.y << std::endl;

	std::cout << "playerPos x: " << playerPos.x << " playerPos y: " << playerPos.y << std::endl;

	glm::vec2 direction = test - glm::vec2(realPos.x, realPos.y);*/
}
glm::vec2 Camera::mouseScreenToWorld(glm::vec2 screenPos)
{
	// Converting (x,y,z) to range [0,1]
	screenPos.x = screenPos.x / windowWidth;
	screenPos.y = screenPos.y / windowHeight;
	//z = gl_FragCoord.z; // Already in range [0,1]

	// Converting from range [0,1] to NDC [-1,1]
	float ndcx = screenPos.x * 2.0 - 1.0;
	float ndcy = 1.0 - screenPos.y * 2.0;// - 1.0;
										 //float ndcz = z * 2.0 - 1.0;
	glm::vec4 ndc = mInverseProjectionMatrix * glm::vec4(ndcx, ndcy, 0.0f, 1.0f);
	//ndc.y *= -1.0f;
	//glm::vec4 ndc = glm::vec4(ndcx, ndcy, 0.0f, 1.0f);
	return glm::vec2(ndc);
}