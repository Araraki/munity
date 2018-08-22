#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D fillTex;
uniform vec4 Color;

void main()
{
	FragColor = texture(fillTex, TexCoords) * Color;
}