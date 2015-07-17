#include <SMOG/Viewport.h>

#include <GL/glew.h>


SMOG_NAMESPACE_ENTER
{
	Viewport::Viewport(uint width, uint height) :
		m_width(width),
		m_height(height)
	{

	}

	void Viewport::resize(uint width, uint height)
	{
		m_width = width;
		m_height = height;
		glViewport(0, 0, m_width, m_height);
	}

	uint Viewport::width() const
	{
		return m_width;
	}

	uint Viewport::height() const
	{
		return m_height;
	}

	void Viewport::clear(bool color /*= true*/, bool depth /*= true*/) const
	{
		GLbitfield mask = 0;
		if (color)
		{
			mask += GL_COLOR_BUFFER_BIT;
		}
		if (depth)
		{
			mask += GL_DEPTH_BUFFER_BIT;
		}
		glClear(mask);
	}
}