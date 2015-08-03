#version 400

uniform sampler2D tex;

in vec2 vert_uv;
out vec4 frag_color;

void main()
{
	frag_color = vec4(texture(tex, vert_uv).rgb, 1.0);
}
