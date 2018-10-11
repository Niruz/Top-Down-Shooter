#pragma once
#include "RendererBase.h"
#include "IndexBuffer.h"

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE   (RENDERER_MAX_SPRITES * 6)

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOR_INDEX  1
class BatchRenderer : public RendererBase
{
public:
	BatchRenderer();
	~BatchRenderer();
	void Begin();
	void Submit(const Renderable* renderable) override;
	void End();
	void Flush() override;

private:
	void Initialize();

	GLuint myVAO;
	IndexBuffer* myIBO;
	GLuint myVBO;
	GLsizei myIndexCount;

	VertexData* myBuffer;
};