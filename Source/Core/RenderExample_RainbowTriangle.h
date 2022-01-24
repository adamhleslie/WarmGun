#pragma once

#include "RenderExample.h"
#include "Shader.h"
#include "GLVertexArray.h"

class RenderExample_RainbowTriangle : public RenderExample
{
public:
	RenderExample_RainbowTriangle();
	
	void Update() override;

private:
	Shader m_shader;
	std::shared_ptr<GLVertexArray> m_triangle;
};


