#version 450

out vec4 f_Color;

// in vec3 Colour;
in vec2 v_Uvs;
uniform sampler2D u_ColorTexture;

void main()
{
	vec4 color = texture(u_ColorTexture, v_Uvs);
	f_Color = color;
}