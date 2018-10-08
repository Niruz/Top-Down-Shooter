#version 330 core
  
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 texCoord;
//layout (location = 2) in float texID;
//layout (location = 3) in vec4 color;


out DATA
{
	vec4 pos;
	vec2 uv;
	//float texID;
	vec4 col;
} vs_out;


uniform mat4 projectionMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 modelMatrix = mat4(1.0);



void main()
{

 //  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position,1);
 gl_Position = vec4(position,1);
   vs_out.pos = /*modelMatrix **/ vec4(position,1);
   vs_out.uv = texCoord;
   vs_out.col = vec4(1.0f,0.0f,0.0f,1.0f);
   //vs_out.texID = texID;
}