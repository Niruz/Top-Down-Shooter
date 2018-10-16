#version 330 core

layout (location = 0) out vec4 color;


in DATA
{
	vec4 pos;
	vec4 col;
	float tid;
	vec2 texCoords;
} fs_in;

uniform vec2 lightPos;
//uniform sampler2D texture2d;
uniform sampler2D textureArray[31];
void main()
{
	float intensity = 50.0f / length(fs_in.pos.xy - lightPos);
   // color = fs_in.col * intensity;
	vec4 texColor = fs_in.col;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		

		texColor = texture(textureArray[tid],fs_in.texCoords);
		/*if(tid == 0)
			texColor = vec4(1.0f,0.0f,0.0f,1.0f);
		if(tid == 1)
			texColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);*/
	}
	//color = texture(texture2d, fs_in.texCoords) *intensity;
	color = texColor * intensity;
} 