#version 330 core

layout (location = 0) out vec4 color;


in DATA
{
	vec4 pos;
	vec4 col;
} fs_in;

uniform vec2 lightPos;

void main()
{
    color = fs_in.col;
} 