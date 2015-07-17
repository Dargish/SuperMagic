#pragma once

#include <SMOG/Renderable.h>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Mesh : public Renderable
	{
	public:
		Mesh();
		virtual ~Mesh();

		uint vbo();
		uint vbo() const;
		
		uint vao();
		uint vao() const;

	private:
		uint m_vbo, m_vao;
	};
}