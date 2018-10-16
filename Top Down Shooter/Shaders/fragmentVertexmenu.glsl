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
	float intensity = 50.0f / length(fs_in.pos.xy - lightPos);
    color = fs_in.col * intensity;
  //  color = fs_in.col;
} 