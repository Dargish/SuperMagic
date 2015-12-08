#version 400

uniform mat4 world;
uniform vec3 color;

in vec3 position;
out vec3 vert_color;

void main()
{
	gl_Position = world * vec4(position, 1.0);
	vert_color = color;
}
