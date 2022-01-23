#version 410 core

uniform vec4 uniformColor; // Uniform variable set on CPU, and accessible to all stages in the shader pipeline
out vec4 FragColor;

void main()
{
    FragColor = uniformColor;
}
