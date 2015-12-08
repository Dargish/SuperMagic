#version 400

uniform mat4 world;

in vec3 position;
in vec2 uv;
out vec2 vert_uv;

void main()
{
	gl_Position = world * vec4(position, 1.0);
	vert_uv = uv;
}
