#include "TileLayer.h"
#include "BatchRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
TileLayer::TileLayer(Shader* shader)
	:Layer(new BatchRenderer(), shader, glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f))
{
//	glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
//	glm::ortho(-650.0f, 650.0f, -370.0f, 370.0f, -1.0f, 1.0f)
}
TileLayer::~TileLayer()
{

}