#version 330 core

layout (location = 0) out vec4 color;


in DATA
{
	vec4 pos;
	vec4 col;
	vec2 texCoords;
} fs_in;

uniform vec2 lightPos;
uniform sampler2D texture;
void main()
{
	
	float intensity = 50.0f / length(fs_in.pos.xy - lightPos);
    color = texture(texture, fs_in.texCoords);
  //  color = fs_in.col;
} 