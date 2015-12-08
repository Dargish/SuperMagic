#include <SMOG/Primitives/Quad.h>

#include <GL/glew.h>
#include <vector>


SMOG_NAMESPACE_ENTER
{
	Quad::Quad()
	{
		std::vector<float> positions = {
			-1.0f,  3.0f,  0.0f,
			 3.0f, -1.0f,  0.0f,
			-1.0f, -1.0f,  0.0f
		};
		std::vector<float> uvs = {
			 0.0f,  2.0f,
			 2.0f,  0.0f,
			 0.0f,  0.0f
		};
		vao().addBuffer(positions, 3);
		vao().addBuffer(uvs, 2);
	}

	void Quad::draw() const
	{
		vao().bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}