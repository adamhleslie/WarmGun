#pragma once

#include "RenderExample.h"
#include "Shader.h"
#include "GLVertexArray.h"

class RenderExample_RectangleAndTriangle : public RenderExample
{
public:
	RenderExample_RectangleAndTriangle();

	void Update() override;

private:
	Shader m_shader;
	std::shared_ptr<GLVertexArray> m_triangle;
	std::shared_ptr<GLVertexArray> m_rectangle;
};


