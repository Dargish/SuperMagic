#include <SMOG/Primitives/Triangle.h>

#include <GL/glew.h>
#include <vector>


SMOG_NAMESPACE_ENTER
{
	Triangle::Triangle()
	{
		std::vector<float> positions = {
			 0.0f,  0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			-0.5f, -0.5f,  0.0f
		};
		std::vector<float> uvs = {
			 0.5f,  0.0f,
			 1.0f,  1.0f,
			 0.0f,  1.0f
		};
		vao().addBuffer(positions, 3);
		vao().addBuffer(uvs, 2);
	}

	void Triangle::draw() const
	{
		vao().bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}