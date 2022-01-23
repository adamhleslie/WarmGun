#version 410 core

in vec4 vertexColor; // Color input from the fragment shader
out vec4 FragColor;

void main()
{
    FragColor = vertexColor;
}
