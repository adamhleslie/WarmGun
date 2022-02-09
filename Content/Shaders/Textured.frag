#version 410 core

in vec3 vertexColor;
in vec2 textureCoordinates;

uniform sampler2D texture2D;

out vec4 FragColor;

void main()
{
    FragColor = texture(texture2D, textureCoordinates) * vec4(vertexColor, 1.0);
}
