#version 400

uniform mat4 world;

in vec3 position;

void main()
{
	gl_Position = world * vec4(position, 1.0);
}
