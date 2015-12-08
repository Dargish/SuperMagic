#version 400

in vec3 vert_color;
layout (location = 0) out vec4 g_diffuse;

void main()
{
	g_diffuse = vec4(vert_color, 1.0);
}
