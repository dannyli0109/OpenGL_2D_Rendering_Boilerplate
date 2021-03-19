#version 450

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_Uvs;

// out vec3 Colour;
out vec2 v_Uvs;

// uniform mat4 vpMatrix;

void main()
{
	v_Uvs = vec2(a_Uvs.x, 1.0 - a_Uvs.y);
	gl_Position = vec4(a_Position * 2.0, 1);
}