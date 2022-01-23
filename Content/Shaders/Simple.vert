#version 410 core

// All vertex shaders should include at least one input, for incoming vertex data
// Layout metadata allows us to configure a vertex attribute that can be referenced from the CPU
// - This step can be skipped in favor of using glGetAttribLocation
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
