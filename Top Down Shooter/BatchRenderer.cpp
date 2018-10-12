#include "BatchRenderer.h"
#include "ShaderManager.h"
// glm::vec3, glm::vec4, glm::ivec4, glm::mat4
#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>
BatchRenderer::BatchRenderer()
{
	Initialize();
}
BatchRenderer::~BatchRenderer()
{
	delete myIBO;
	glDeleteBuffers(1, &myVBO);
}
void BatchRenderer::Initialize()
{
	glGenVertexArrays(1, &myVAO);
	glGenBuffers(1, &myVBO);

	glBindVertexArray(myVAO);
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(4*sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//GLushort indices[RENDERER_INDICES_SIZE];
	GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
	int offset = 0;
	for(int i = 0; i< RENDERER_INDICES_SIZE; i+=6)
	{
		indices[  i  ] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	myIBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	glBindVertexArray(0);

	delete[] indices;
}
void BatchRenderer::Begin()
{
/*	ShaderMan->bindShader(SIMPLE_FORWARD_SHADER);
	//glm::mat4 ortho = glm::ortho(-640.0f, 640.0f, -360.0f, 360.0f, -1.0f, 1.0f);
	glm::mat4 ortho = glm::ortho(-650.0f, 650.0f, -370.0f, 370.0f, -1.0f, 1.0f);
	ShaderMan->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, ortho);
	*/
	glBindBuffer(GL_ARRAY_BUFFER, myVBO);
	myBuffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}
void BatchRenderer::End()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void BatchRenderer::Submit(const Renderable* renderable) 
{
	const glm::vec3& position = renderable->GetPosition(); //glm::vec4(renderable->GetPosition(), 1.0f);
	const glm::vec2& size     = renderable->GetSize();
	const glm::vec4& color    = renderable->GetColor();

	int r = color.x * 255.0f;
	int g = color.y * 255.0f;
	int b = color.z * 255.0f;
	int a = color.w * 255.0f;

	unsigned int c = a << 24 | b << 16 | g << 8 | r;

	myBuffer->vertex = /*position;*/ glm::vec3(*myTransformationStackBack * glm::vec4(position,1.0f));
	myBuffer->color  = c;
	myBuffer++;

	myBuffer->vertex = glm::vec3(*myTransformationStackBack  *glm::vec4(position.x, position.y + size.y, position.z,1));
	myBuffer->color = c;
	myBuffer++;

	myBuffer->vertex = glm::vec3(*myTransformationStackBack  *glm::vec4(position.x + size.x, position.y + size.y, position.z,1));
	myBuffer->color = c;
	myBuffer++;

	myBuffer->vertex = glm::vec3(*myTransformationStackBack  *glm::vec4(position.x + size.x, position.y, position.z,1));
	myBuffer->color = c;
	myBuffer++;

	myIndexCount += 6;
}

void BatchRenderer::Flush()
{
	glBindVertexArray(myVAO);
	myIBO->bind();

	//glDrawElements(GL_TRIANGLES, myIndexCount, GL_UNSIGNED_SHORT, nullptr);
	glDrawElements(GL_TRIANGLES, myIndexCount, GL_UNSIGNED_INT, nullptr);
	myIBO->unbind();
	glBindVertexArray(0);

	myIndexCount = 0;

//	ShaderMan->unbindShader();
}