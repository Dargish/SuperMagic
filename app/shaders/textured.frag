#version 400

uniform sampler2D tex;
in vec2 vert_uv;

layout (location = 0) out vec4 g_diffuse;

void main()
{
	g_diffuse = texture(tex, vert_uv);
}
