#pragma once

#include "RenderExample.h"
#include "Shader.h"
#include "GLVertexArray.h"

class RenderExample_TexturedTriangle : public RenderExample
{
public:
	RenderExample_TexturedTriangle();

	void Render() override;

private:
	Shader m_shader;
	std::shared_ptr<GLVertexArray> m_triangle;
};


