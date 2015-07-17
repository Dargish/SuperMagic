#include <SMOG/Primitives/Triangle.h>

#include <GL/glew.h>

SMOG_NAMESPACE_ENTER
{
	Triangle::Triangle()
	{
		float points[] = {
			 0.0f,  0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			-0.5f, -0.5f,  0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, vbo());
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
		glBindVertexArray(vao());
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	}

	void Triangle::draw() const
	{
		glBindVertexArray(vao());
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}