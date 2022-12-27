// ********************************************************************** //
//                                                                        //
//             vector.hpp                                                 //
//             Created: 2022/12/06 23:04:53 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef VECTOR_HPP
# define VECTOR_HPP
# define CYAN "\033[1;36m"
# define MG "\033[1;35m"
# define JJ "\033[1;31m"
# define WD "\033[1;0m"
# define SHOW(...) std::cout << CYAN << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl


#include "type_traits.hpp"
#include <iostream>
#include <memory>
#include "iterator.hpp"
#include "algorithm.hpp"
#include "type_traits.hpp"
#include "util.hpp"
#include "random_access_iterator.hpp"

namespace ft {
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		// ====================================================== //
		// ==================== Member types ==================== //
		// ====================================================== //

		typedef Allocator											allocator_type;
		typedef	T													value_type;
		typedef	long int											difference_type;	// FIXME: not sure, maybe we'll need iterator
		typedef	size_t												size_type;			// FIXME: not sure yet
		typedef	T&													reference;
		typedef	const T&											const_reference;
		typedef	T*													pointer;
		typedef	const T*											const_pointer;

		typedef typename ft::random_access_iterator<T>				iterator;				// TODO: vector-um senc mi ban er grac
		typedef typename ft::random_access_iterator<const T>		const_iterator;
		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;


		// ====================================================== //
		// ================== Member functions ================== //
		// ====================================================== //

	public:

		// -- default constructor - //
		explicit vector(const allocator_type& __alloc = allocator_type()): _alloc(__alloc), _size(0), _capacity(0)
		{
			_vptr = _alloc.allocate(1);
		}

		//  constructor with 'size' and 'n' elemets to be filled  //
		explicit vector(size_type __n, const value_type& __x = value_type(), const allocator_type& __alloc = allocator_type()):
			_alloc(__alloc), _size(__n), _capacity(__n)
		{
			_vptr = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(&_vptr[i], __x);
		}

		//  constructor with other vector's iterators start and end  //
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& __alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) :
				_alloc(__alloc), _size(0) {
			InputIterator	it(first);
			while (it++ != last)
				++_size;
			
			_capacity = _size;
			_vptr = _alloc.allocate(_capacity);
			for (int i = 0; first != last; ++first, ++i)
				_alloc.construct(&_vptr[i], *first);
		}

		//  copy constructor, but needs testing  //
		vector(const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			this->_vptr = _alloc.allocate(_capacity);
			// size_type n = _size;
			// pointer m_p = _vptr, other = x._vptr;
			size_t i = 0;
			for (const_iterator it = x.begin(); it != x.end(); ++i, ++it)
				_alloc.construct(&_vptr[i], *it);
			// while (n--)
			// 	_alloc.construct(m_p++, *other++);
		}

		// - assignement operator - //
		vector&	operator=(const vector& x)
		{
			if (this != &x)
			{
				this->clear();
				this->insert(_vptr, x.begin(), x.end());
			}
			return *this;
		}

		// ------ destructor ------ //
		~vector()
		{
			this->clear();
			this->_alloc.deallocate(_vptr, capacity());
			// for (iterator it = begin(); it != end(); ++it)
			// 	_alloc.destroy(&(*(it)));					// FIXME: not sure about the syntax
			// _alloc.deallocate(_vptr, _capacity);
		}

		//  replaces the contents with copies of those in the range [first, last]  //
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			clear();
			size_type n = ft::difference(first, last);		// TODO: maybe I have to write for this std::distance
			if (n > _capacity)
			{
				_alloc.deallocate(_vptr, _capacity);
				_capacity = n;
				_vptr = _alloc.allocate(n);
			}
			size_type i = 0;
			for (; first != last; ++i, ++first)
				_alloc.construct(&_vptr[i], *first);
			_size = i;
		}

		//  replaces the contents with count copies of value value  //
		void	assign(size_type count, const value_type& value)
		{
			clear();

			if (count > _capacity)
			{
				_alloc.deallocate(_vptr, _capacity);
				_vptr = _alloc.allocate(count);
				_capacity = count;
			}
			for (size_type i = 0; i < count; ++i)
				_alloc.construct(&_vptr[i], value);
		}

		allocator_type& get_allocator() const { return this->_alloc; } // FIXME: maybe this has to be const

		// ====================================================== //
		// ====================== Iterators ===================== //
		// ====================================================== //

		iterator				begin() 		{ return iterator(_vptr); }
		const_iterator			begin() const 	{ return const_iterator(_vptr); }
		iterator				end() 			{ return iterator(_vptr + _size); }
		const_iterator			end() const 	{ return const_iterator(_vptr + _size); } // FIXME: needs work
		reverse_iterator		rbegin() 		{ return reverse_iterator(_vptr + _size - 1); }
		const_reverse_iterator	rbegin() const 	{ return const_reverse_iterator(_vptr + _size - 1); }
		reverse_iterator		rend() 			{ return reverse_iterator(_vptr - 1); }
		const_reverse_iterator	rend() const 	{ return const_reverse_iterator(_vptr - 1); }
		
		// ====================================================== //
		// ====================== Capacity ====================== //
		// ====================================================== //

		size_type	size() const { return _size; }
		size_type	max_size() const { return _alloc.max_size() / sizeof(value_type); }				// FIXME: maybe need to change this part. I'll test later
		
		//  changes the _size; _size > __n ? _size = _n : allocate & fill with default value  //
		// void	resize(size_type __n, value_type __val = value_type())
		// {
		// 	if (_size == __n)
		// 		return;
		// 	if (__n > max_size())
		// 		throw std::out_of_range("ft::vector");
		// 	if (__n > _capacity)
		// 		insert(_vptr + _size, __n - _size, __val);
		// 	_size = __n;
		// }

		void	resize (size_type n, value_type val = value_type())
	{
		if (n > _size)
		{
			if (n > _capacity)
			{
				if (n > _capacity * 2)
					this->reserve(n);
				else if (_capacity > 0)
					this->reserve(_capacity * 2);
				else
					this->reserve(1);
			}

			for (size_type i = _size ; i < n ; i++)
				_alloc.construct(_vptr + i, val);
		}
		else
		{
			for (size_type i = n ; i < _size ; i++)
				_alloc.destroy(_vptr + i);
		}

		_size = n;
	}

		size_type	capacity() const	{ return _capacity; }
		bool		empty() const		{ return _size == 0; }

		//  reserves memory; __n < _capacity ? return : realloc  //
		void	reserve(size_type __n)
		{
			if (__n > max_size())
				throw std::out_of_range("ft::vector");
			if (__n > _capacity)
			{
				pointer	start = _vptr;
				pointer	end = _vptr + _size;
				size_type	prev_capacity = this->_capacity;
				this->_vptr = _alloc.allocate(__n);
				pointer tmp = _vptr;
				this->_capacity = __n;

				for (pointer it = start; it != end; ++it)
					_alloc.construct(tmp++, *it);
				for (size_type len = end - start; len > 0; --len)
					_alloc.destroy(--end);
				_alloc.deallocate(start, prev_capacity);
			}
		}

		// ====================================================== //
		// =================== Element access =================== //
		// ====================================================== //

		//  returns __n < _capacity ? __n-th element : type's default value (ex. for int – 0) //
		reference	operator[] (size_type __n)
		{
			// if (__n < _capacity)						TODO: I can't return value_type for reference
				return _vptr[__n];
			// return value_type();
		}

		const_reference	operator[] (size_type __n) const
		{
			if (__n < _capacity)
				return _vptr[__n];
			return value_type();
		}

		reference	at(size_type __n)
		{
			if (__n >= _capacity)
				throw std::out_of_range("ft::vector");
			return _vptr[__n];
		}

		const_reference	at(size_type __n) const
		{
			if (__n >= _capacity)
				throw std::out_of_range("ft::vector");
			if (__n >= _size)
				return value_type();
			return _vptr[__n];
		}

		//  if we need first or last elements  //
		reference front()				{ return _vptr[0]; }
		const_reference front()	const	{ return _vptr[0]; }
		reference back()				{ return _vptr[_size - 1]; }
		const_reference back()	const	{ return _vptr[_size - 1]; }


		// ====================================================== //
		// ====================== Modifiers ===================== //
		// ====================================================== //

		//  appends the fiven element value to the end of the container  //
		void	push_back (const value_type& value)
		{ 
			if (_size + 1 > _capacity)
			{
				size_type papacity = (_size == 0 ? 1 : _size * 2);
				reserve(papacity);
			}
			_alloc.construct(&_vptr[_size++], value);
		}

		//  removes the last element in the vector  //
		void	pop_back()
		{
			if (_size)
				_alloc.destroy(&_vptr[--_size]);
		}
		
		//  inserts elements at the specified location in the container  //
		iterator insert(iterator position, const value_type& val)
		{
			difference_type	place = position - begin();
			insert(position, 1, val);
			return iterator(&_vptr[place]);
		}


		void	insert(iterator position, size_type n, const value_type& val)
		{
			difference_type place = position - begin();
			if (_size + n < _capacity)
				realloc(_capacity + n);
			iterator	tmp(&_vptr[place]);
			if (tmp != end())
				rightShift(tmp, n);
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*tmp++), val);
			_size += n;
		}

		//  inserts elements 'first'–'last' after position  //
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			size_type		n = 0;
			InputIterator	it(first);
			difference_type	idx = position - begin();
			iterator	n_pos(&_vptr[idx]);

			while (it++ != last)
				++n;

			if (_size + n > _capacity)
				realloc(_size + n);
			if (n_pos != end())
				rightShift(n_pos, n);
			
			for (size_type i = 0; i < n; ++i)
				_alloc.construct(&(*n_pos++), *first++);
			_size += n;
		}

		//  removes from the vector a single element  //
		iterator	erase (iterator position)
		{
			return	erase(position, position + 1);
		}

		//  removes from the vector all elements it given range  & returns new iterator first //
		iterator	erase (iterator first, iterator last)
		{
			if (first == end() || first == last)
				return first;

			difference_type	idx = first - begin();
			if (last < end())
			{
				_size -= static_cast<size_type>(last - first);
				for (; first != end(); ++first, ++last)
				{
					_alloc.destroy(&(*first));
					if (last != end())
						_alloc.construct(&(*first), *last);
				}
			}
			else
			{
				size_type tmp = _size - static_cast<size_type>(last - first);
				while (_size != tmp)
					pop_back();
			}
			return iterator(&_vptr[idx]);
		}

		//  swaps two vectors << only by pointer >>  //
		void	swap (vector& x)
		{
			if (x == *this)
				return;
			allocator_type	tmp_alloc = this->_alloc;
			pointer			tmp_vptr = this->_vptr;
			size_type		tmp_size = this->_size;
			size_type		tmp_capacity = this->_capacity;

			this->_alloc = x._alloc;
			this->_vptr = x._vptr;
			this->_size = x._size;
			this->_capacity = x._capacity;

			x._alloc = tmp_alloc;
			x._vptr = tmp_vptr;
			x._size = tmp_size;
			x._capacity = tmp_capacity;	
		}

		//  removes all elements from the vector and destroys em  //
		void	clear()
		{
			for (size_type i = 0; i < _size; ++i)					// FIXME: or maybe just _size = 0 :)
				_alloc.destroy(&_vptr[i]);
		}

		
		// ====================================================== //
		// ===================== member data ==================== //
		// ====================================================== //
	private:
		allocator_type	_alloc; 	// allocator object
		pointer			_vptr; 		// array pointer
		size_type		_size;		// number of elements in vector
		size_type		_capacity;	// allocated memory size


		// ====================================================== //
		// ======================== utils ======================= //
		// ====================================================== //

		//  method for memory reallocation  //
		void	realloc(size_type papacity)
		{
			pointer	ptr = _alloc.allocate(papacity);
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(&ptr[i], _vptr[i]);
			this->~vector();								// FIXME: not sure if this's safe
			_capacity = papacity;
			_vptr = ptr;
		}

		//  shifting elements from 'it' position 'step' steps right  //
		void	rightShift (iterator it, size_type step)
		{
			if (!step)
				return;
			iterator	i = end() - 1;
			do {
				_alloc.construct(&(*(i + step)), *i);
				_alloc.destroy(&(*i));
			}
			while (i-- != it);
		}


	};

	// ====================================================== //
	// ================ Non-Member overloads ================ //
	// ====================================================== //


	//  == != < > <= >= operator overloads  //

	template < class T, class Alloc >
	bool operator== (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());							// TODO: implement ft::equal
	}

	template < class T, class Alloc >
	bool operator!= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template < class T, class Alloc >
	bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());	//TODO: implement ft::lexicographical_compare
	}

	template < class T, class Alloc >
	bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template < class T, class Alloc >
	bool operator<= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return	(!(rhs < lhs));
	}

	template < class T, class Alloc >
	bool operator>= (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	// - swap vector contents - //
	template < class T, class Alloc >
	void swap (vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}

}	// namespace ft

# endif	// VECTOR_HPP
