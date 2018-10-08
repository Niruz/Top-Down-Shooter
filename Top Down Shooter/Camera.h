#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(const glm::mat4& projection)
		: mProjectionMatrix(projection)
	{
		mInverseProjectionMatrix = glm::inverse(mProjectionMatrix);
	};
	~Camera();

	void setProjectionMatrix(const glm::mat4& projection)
	{
		mProjectionMatrix = projection;
		mInverseProjectionMatrix = glm::inverse(mProjectionMatrix);
	}
	void setPosition(const glm::vec3& position);

	glm::vec2 mouseScreenToWorld(glm::vec2 screenPos);

	glm::vec2 getPlayerDirection(const glm::vec3& pos);
	glm::mat4 getProjectionMatrix() const { return mProjectionMatrix; };
	glm::vec3 getPosition() const { return mPosition; };

	void setScreenPosition(const glm::vec2& pos);
	void setWidth(float width) { windowWidth = width; };
	void setHeight(float height) { windowHeight = height; };

public:

	glm::mat4 mProjectionMatrix;
	glm::mat4 mInverseProjectionMatrix;
	glm::mat4 mTranslationMatrix;

	glm::vec3 mPosition;

	glm::vec2 screenPosition;

	float windowWidth;
	float windowHeight;
};