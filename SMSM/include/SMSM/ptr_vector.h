#pragma once

#include <vector>

SMSM_NAMESPACE_ENTER
{
	template<class T>
	class ptr_vector_iterator;
	template<class T>
	class ptr_vector_const_iterator;

	template<class T>
	class ptr_vector
	{
	public:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef ptr_vector_iterator<T> iterator;
		typedef ptr_vector_const_iterator<T> const_iterator;
		typedef typename std::vector<T*>::size_type size_type;

		struct iterator_range
		{
			iterator_range()
			{ }

			iterator_range(iterator begin, iterator end) :
				begin(begin), end(end)
			{ }

			iterator begin;
			iterator end;
		};

		struct const_iterator_range
		{
			const_iterator_range()
			{ }
			
			const_iterator_range(const_iterator begin, const_iterator end) :
				begin(begin), end(end)
			{ }

			const_iterator begin;
			const_iterator end;
		};

		ptr_vector();
		ptr_vector(const ptr_vector& other);
		ptr_vector& operator=(const ptr_vector& other);

		virtual ~ptr_vector();

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		iterator_range range();
		const_iterator_range range() const;

		size_type size() const;

		void push_back(pointer ptr);
		void pop_back();

		reference back();
		const_reference back() const;

		reference front();
		const_reference front() const;

		reference operator[] (size_type i);
		const_reference operator[] (size_type i) const;

		void erase(size_type i);
		void erase(iterator it);

	private:
		std::vector<T*> m_vector;
	};

	template<class T>
	class ptr_vector_iterator
	{
		friend class ptr_vector<T>;
		friend class ptr_vector_const_iterator<T>;
	public:
		typedef T& reference;
		typedef T* pointer;
		typedef typename std::vector<T*>::iterator inner_iterator;

		ptr_vector_iterator();
		ptr_vector_iterator(inner_iterator inner);
		ptr_vector_iterator(const ptr_vector_iterator& other);
		ptr_vector_iterator& operator=(const ptr_vector_iterator& other);
		bool operator==(const ptr_vector_iterator& other) const;
		bool operator!=(const ptr_vector_iterator& other) const;
		ptr_vector_iterator& operator++();
		reference operator*();
		pointer operator->();

	private:
		inner_iterator m_inner;
	};

	template<class T>
	class ptr_vector_const_iterator
	{
		friend class ptr_vector<T>;
	public:
		typedef const T& reference;
		typedef const T* pointer;
		typedef typename std::vector<T*>::const_iterator inner_iterator;

		ptr_vector_const_iterator();
		ptr_vector_const_iterator(inner_iterator inner);
		ptr_vector_const_iterator(const ptr_vector_const_iterator& other);
		ptr_vector_const_iterator(const ptr_vector_iterator<T>& other);
		ptr_vector_const_iterator& operator=(const ptr_vector_const_iterator& other);
		ptr_vector_const_iterator& operator=(const ptr_vector_iterator<T>& other);
		bool operator==(const ptr_vector_const_iterator& other) const;
		bool operator!=(const ptr_vector_const_iterator& other) const;
		ptr_vector_const_iterator& operator++();
		reference operator*();
		pointer operator->();

	private:
		inner_iterator m_inner;
	};

	template<class T>
	ptr_vector<T>::ptr_vector()
	{

	}

	template<class T>
	ptr_vector<T>::~ptr_vector()
	{
		for(size_type i = 0; i < size(); ++i)
		{
			delete m_vector[i];
		}
	}

	template<class T>
	typename ptr_vector<T>::iterator ptr_vector<T>::begin()
	{
		return iterator(m_vector.begin());
	}

	template<class T>
	typename ptr_vector<T>::const_iterator ptr_vector<T>::begin() const
	{
		return const_iterator(m_vector.begin());
	}

	template<class T>
	typename ptr_vector<T>::iterator ptr_vector<T>::end()
	{
		return iterator(m_vector.end());
	}

	template<class T>
	typename ptr_vector<T>::const_iterator ptr_vector<T>::end() const
	{
		return const_iterator(m_vector.end());
	}

	template<class T>
	typename ptr_vector<T>::iterator_range ptr_vector<T>::range()
	{
		return iterator_range(begin(), end());
	}

	template<class T>
	typename ptr_vector<T>::const_iterator_range ptr_vector<T>::range() const
	{
		return const_iterator_range(begin(), end());
	}

	template<class T>
	typename ptr_vector<T>::size_type ptr_vector<T>::size() const
	{
		return m_vector.size();
	}

	template<class T>
	void ptr_vector<T>::push_back(pointer ptr)
	{
		m_vector.push_back(ptr);
	}

	template<class T>
	void ptr_vector<T>::pop_back()
	{
		delete m_vector.back();
		m_vector.pop_back();
	}

	template<class T>
	typename ptr_vector<T>::reference ptr_vector<T>::back()
	{
		return *m_vector.back();
	}

	template<class T>
	typename ptr_vector<T>::const_reference ptr_vector<T>::back() const
	{
		return *m_vector.back();
	}

	template<class T>
	typename ptr_vector<T>::reference ptr_vector<T>::front()
	{
		return *m_vector.front();
	}

	template<class T>
	typename ptr_vector<T>::const_reference ptr_vector<T>::front() const
	{
		return *m_vector.front();
	}

	template<class T>
	void ptr_vector<T>::erase(size_type i)
	{
		typename std::vector<T*>::iterator it = m_vector.begin() + i;
		delete *it;
		m_vector.erase(it);
	}

	template<class T>
	void ptr_vector<T>::erase(iterator it)
	{
		m_vector.erase(it.m_inner);
	}

	template<class T>
	typename ptr_vector<T>::reference ptr_vector<T>::operator[] (size_type i)
	{
		return *m_vector[i];
	}

	template<class T>
	typename ptr_vector<T>::const_reference ptr_vector<T>::operator[] (size_type i) const
	{
		return *m_vector[i];
	}


	/*
	* ptr_vector_iterator implementation
	*/

	template<class T>
	ptr_vector_iterator<T>::ptr_vector_iterator()
	{

	}

	template<class T>
	ptr_vector_iterator<T>::ptr_vector_iterator(inner_iterator inner) :
		m_inner(inner)
	{

	}

	template<class T>
	ptr_vector_iterator<T>::ptr_vector_iterator(const ptr_vector_iterator& other) :
		m_inner(other.m_inner)
	{

	}

	template<class T>
	ptr_vector_iterator<T>& ptr_vector_iterator<T>::operator=(const ptr_vector_iterator& other)
	{
		m_inner = other.m_inner;
		return *this;
	}

	template<class T>
	bool ptr_vector_iterator<T>::operator==(const ptr_vector_iterator& other) const
	{
		return m_inner == other.m_inner;
	}

	template<class T>
	bool ptr_vector_iterator<T>::operator!=(const ptr_vector_iterator& other) const
	{
		return m_inner != other.m_inner;
	}

	template<class T>
	ptr_vector_iterator<T>& ptr_vector_iterator<T>::operator++()
	{
		++m_inner;
		return *this;
	}

	template<class T>
	typename ptr_vector_iterator<T>::reference ptr_vector_iterator<T>::operator*()
	{
		return **m_inner;
	}

	template<class T>
	typename ptr_vector_iterator<T>::pointer ptr_vector_iterator<T>::operator->()
	{
		return *m_inner;
	}


	/*
	* ptr_vector_const_iterator implementation
	*/

	template<class T>
	ptr_vector_const_iterator<T>::ptr_vector_const_iterator()
	{

	}

	template<class T>
	ptr_vector_const_iterator<T>::ptr_vector_const_iterator(inner_iterator inner) :
		m_inner(inner)
	{

	}

	template<class T>
	ptr_vector_const_iterator<T>::ptr_vector_const_iterator(const ptr_vector_const_iterator& other) :
		m_inner(other.m_inner)
	{

	}

	template<class T>
	ptr_vector_const_iterator<T>::ptr_vector_const_iterator(const ptr_vector_iterator<T>& other) :
		m_inner(other.m_inner)
	{

	}

	template<class T>
	ptr_vector_const_iterator<T>& ptr_vector_const_iterator<T>::operator=(const ptr_vector_const_iterator& other)
	{
		m_inner = other.m_inner;
		return *this;
	}

	template<class T>
	ptr_vector_const_iterator<T>& ptr_vector_const_iterator<T>::operator=(const ptr_vector_iterator<T>& other)
	{
		m_inner = other.m_inner;
		return *this;
	}

	template<class T>
	bool ptr_vector_const_iterator<T>::operator==(const ptr_vector_const_iterator& other) const
	{
		return m_inner == other.m_inner;
	}

	template<class T>
	bool ptr_vector_const_iterator<T>::operator!=(const ptr_vector_const_iterator& other) const
	{
		return m_inner != other.m_inner;
	}

	template<class T>
	ptr_vector_const_iterator<T>& ptr_vector_const_iterator<T>::operator++()
	{
		++m_inner;
		return *this;
	}

	template<class T>
	typename ptr_vector_const_iterator<T>::reference ptr_vector_const_iterator<T>::operator*()
	{
		return **m_inner;
	}

	template<class T>
	typename ptr_vector_const_iterator<T>::pointer ptr_vector_const_iterator<T>::operator->()
	{
		return *m_inner;
	}
}
