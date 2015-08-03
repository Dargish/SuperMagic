#pragma once

#include <SMOG/SMOG.h>
#include <SMOG/VertexBuffer.h>

#include <vector>


SMOG_NAMESPACE_ENTER
{
	class SMOGAPI VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		uint vao() const;

		uint count() const;

		void bind() const;

		void addBuffer(
			const VertexBuffer& buffer,
			int componentSize,
			bool normalised = false,
			size_t stride = 0,
			void* offset = NULL);

		template<typename T>
		void addBuffer(
			const std::vector<T>& data,
			int componentSize,
			bool normalised = false,
			size_t stride = 0,
			void* offset = NULL);

	private:
		uint m_vao;
		std::vector<uint> m_vbos;
		uint m_count;
	};

	template<typename T>
	void VertexArray::addBuffer(
		const std::vector<T>& data,
		int componentSize,
		bool normalised /*= false*/,
		size_t stride /*= 0*/,
		void* offset /*= NULL*/)
	{
		VertexBuffer buffer;
		buffer.bind();
		buffer.bufferData(data);
		addBuffer(buffer, componentSize, normalised, stride, offset);
	}
}