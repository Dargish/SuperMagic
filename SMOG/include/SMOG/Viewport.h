#pragma once

#include <SMOG/SMOG.h>

SMOG_NAMESPACE_ENTER
{
	class SMOGAPI Viewport
	{
	public:
		Viewport(uint width, uint height);

		void resize(uint width, uint height);

		uint width() const;
		uint height() const;

		void clear(bool color = true, bool depth = true) const;

	private:
		uint m_width, m_height;
	};
}