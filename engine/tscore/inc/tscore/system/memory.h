/*
	Memory header - provides helper classes for memory management
*/

#pragma once

#include <tscore/types.h>
#include <memory>
#include <vector>

#define ALIGN(x) __declspec(align(x))

namespace ts
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template <int X = 32>
	class Aligned
	{
	public:
			
		void* operator new(std::size_t n){ return _aligned_malloc(n, X); }
		void operator delete(void * p) throw() { _aligned_free(p); }
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	class IAllocator
	{
	public:

		//Memory block type
		typedef void* block;

		virtual block allocate(size_t sz) = 0;
		virtual void free(block mem) = 0;
	};

	/////////////////////////////////////////////////////////////////////////////

	class DefaultAllocator : public IAllocator
	{
	public:

		block allocate(size_t sz) override { return malloc(sz); }
		void free(block mem) override { free(mem); }
	};
	*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename t>
	using UniquePtr = std::unique_ptr<t>;

	template<typename t>
	using SharedPtr = std::shared_ptr<t>;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	class MemoryBuffer
	{
	private:

		void* m_data = nullptr;
		size_t m_size = 0;

	public:

		void* pointer() { return m_data; }
		const void* pointer() const { return m_data; }
		size_t size() const { return m_size; }

		MemoryBuffer() {}

		MemoryBuffer(size_t reserve)
		{
			m_data = new byte[reserve];
			m_size = reserve;
		}

		MemoryBuffer(const void* data, size_t size) :
			m_size(size)
		{
			m_data = new byte[m_size];
			memcpy_s(m_data, m_size, data, size);
		}

		explicit MemoryBuffer(const MemoryBuffer& copy)
		{
			if (m_data)
				delete[] m_data;

			m_size = copy.m_size;

			if (m_data = new byte[m_size]) {}
			else
				throw std::exception("malloc failed to allocate enough memory");

			memcpy(m_data, copy.m_data, m_size);
		}

		MemoryBuffer(MemoryBuffer&& copy)
		{
			m_data = copy.m_data;
			m_size = copy.m_size;

			copy.m_data = nullptr;
			copy.m_size = 0;
		}

		MemoryBuffer& operator=(const MemoryBuffer& copy)
		{
			if (m_data)
				delete[] m_data;

			m_size = copy.m_size;

			if (m_data = new byte[m_size]) {}
			else
				throw std::exception("malloc failed to allocate enough memory");

			memcpy(m_data, copy.m_data, m_size);

			return *this;
		}

		MemoryBuffer& operator=(MemoryBuffer&& copy)
		{
			m_data = copy.m_data;
			m_size = copy.m_size;

			copy.m_data = nullptr;
			copy.m_size = 0;

			return *this;
		}

		~MemoryBuffer()
		{
			if (m_data)
				delete[] m_data;
		}
	};

	template<typename T> inline
		MemoryBuffer make_buffer(const T& t)
	{
		return MemoryBuffer(&t, sizeof(T));
	}

	template<typename T> inline
		MemoryBuffer make_buffer_from_vector(const std::vector<T>& v)
	{
		return MemoryBuffer((const void*)&v[0], v.size() * sizeof(T));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

}