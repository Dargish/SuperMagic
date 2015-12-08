#pragma once

#include <SMOG/SMOG.h>

#include <vector>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI VertexBuffer
	{
	public:
		struct Usage
		{
			enum Frequency
			{
				kStream = 0,
				kStatic,
				kDynamic
			};
			enum Access
			{
				kDraw = 0,
				kRead,
				kCopy
			};
		};

		VertexBuffer();

		uint buffer() const;

		uint type() const;

		void bind() const;

		template<typename T>
		void bufferData(
			std::vector<T> data,
			Usage::Frequency frequency = Usage::kStatic,
			Usage::Access access = Usage::kDraw);

	private:
		template<typename T>
		uint glType() const;

		void bufferData(
			size_t size,
			void* data,
			Usage::Frequency frequency = Usage::kStatic,
			Usage::Access access = Usage::kDraw);

		uint m_vbo;
		uint m_type;
	};


	template<typename T>
	uint VertexBuffer::glType() const
	{
		return 0;
	}

	template<typename T>
	void VertexBuffer::bufferData(
		std::vector<T> data,
		Usage::Frequency frequency /*= Usage::kStatic*/,
		Usage::Access access /*= Usage::kDraw*/)
	{
		m_type = glType<T>();
		bufferData(
			sizeof(T) * data.size(),
			(void*)&data.front(),
			frequency,
			access);
	}
}