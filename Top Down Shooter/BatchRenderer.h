#pragma once
#include "RendererBase.h"
#include "VertexArray.h"

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE   (RENDERER_MAX_SPRITES * 6)
class BatchRenderer : public RendererBase
{
public:
	BatchRenderer();
	~BatchRenderer();
	void Submit(const Renderable* renderable) override;
	void Flush() override;

private:
	void Initialize();

	VertexArray* myVAO;
	IndexBuffer* myIBO;
	GLuint myVBO;
	GLsizei mIndexCount;
};