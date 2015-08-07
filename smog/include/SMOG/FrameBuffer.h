#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/Texture.h>

#include <map>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI FrameBuffer
	{
	public:
		FrameBuffer(
			size_t width = 0,
			size_t height = 0);

		void deleteBuffer();

		uint buffer() const;

		void bind() const;
		void unbind() const;

		// Getters
		size_t width() const;
		size_t height() const;

		// Setters
		void setSize(size_t width, size_t height);

		const Texture& addTarget(
			const std::string& name,
			size_t channels,
			Texture::Format format);

		const Texture& target(const std::string& name) const;

	private:
		void ensureComplete() const;
		
		typedef std::map<std::string, Texture> TargetMap;
		uint m_fbo;
		size_t m_width, m_height;
		Texture m_depthTexture;
		TargetMap m_targetMap;
	};
}