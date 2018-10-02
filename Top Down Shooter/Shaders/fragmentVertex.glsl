#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
//uniform vec2 light_pos;

in DATA
{
	vec4 pos;
    vec2 uv;
  //  float texID;
	vec4 col;
} fs_in;

//uniform sampler2D textures[32];
uniform sampler2D texture;

void main()
{
    
 //  float intensity = 1.0 / length(fs_in.pos.xy - light_pos);
   vec4 texColor = fs_in.col;
   /*if(fs_in.texID > 0.0)
   {
        int tid = int(fs_in.texID - 0.5);
        texColor =  fs_in.col * texture(textures[tid], fs_in.uv);
   }
   */
  // texColor = vec4(texture( myTextureSampler, UV ).rgb,1.0f);
 // texColor = texture(texture,fs_in.uv);
 texColor = texture2D(texture,fs_in.uv);

    color = texColor;// * intensity;


} 