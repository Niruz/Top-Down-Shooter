#include "TileLayer.h"
#include "BatchRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
TileLayer::TileLayer(Shader* shader)
	:Layer(new BatchRenderer(), shader, glm::ortho(-650.0f, 650.0f, -370.0f, 370.0f, -1.0f, 1.0f))
{

}
TileLayer::~TileLayer()
{

}