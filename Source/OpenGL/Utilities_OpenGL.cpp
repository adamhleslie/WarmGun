#include "Utilities_OpenGL.h"

void Utilities::Render_ClearToColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}