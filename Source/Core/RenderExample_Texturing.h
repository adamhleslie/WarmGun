#pragma once

#include "RenderExample.h"
#include "Shader.h"
#include "GLVertexArray.h"
#include "GLTexture.h"

class RenderExample_Texturing : public RenderExample
{
public:
	RenderExample_Texturing();

	void Render() override;

private:
	Shader m_shader;
	std::shared_ptr<GLVertexArray> m_rectangle;
	std::shared_ptr<GLTexture> m_texture1;
	std::shared_ptr<GLTexture> m_texture2;
};


