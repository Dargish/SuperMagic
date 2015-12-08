#version 400

uniform sampler2D diffuse;

in vec2 vert_uv;
out vec4 frag_color;

void main()
{
	frag_color = vec4(texture(diffuse, vert_uv).rga, 1.0);
	//frag_color = vec4(vert_uv.x, 0.0, vert_uv.y, 1.0);
}
