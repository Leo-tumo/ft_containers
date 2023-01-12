// ********************************************************************** //
//                                                                        //
//             vector.hpp                                                 //
//             Created: 2022/12/06 23:04:53 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //


#include "vector"
#ifndef VECTOR_HPP
# define VECTOR_HPP
# define CYAN "\033[1;36m"
# define MG "\033[1;35m"
# define JJ "\033[1;31m"
# define WD "\033[1;0m"
# define SHOW(...) std::cout << CYAN << #__VA_ARGS__ << " == " << __VA_ARGS__ << std::endl
# define LOG(x)	std::cout << MG << x << WD << std::endl;


#include <algorithm>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>

#include "iterator.hpp"
#include "utility.hpp"
#include "random_access_iterator.hpp"

namespace ft {
	template <typename T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		// ====================================================== //
		// ==================== Member types ==================== //
		// ====================================================== //

    typedef T                                        			value_type;
    typedef Allocator                                			allocator_type;
    typedef typename allocator_type::size_type       			size_type;
    typedef typename allocator_type::difference_type 			difference_type;
    typedef value_type&                              			reference;
    typedef const value_type&                        			const_reference;
    typedef typename allocator_type::pointer         			pointer;
    typedef typename allocator_type::const_pointer   			const_pointer;
    typedef random_access_iterator<pointer, vector>         	iterator;
    typedef random_access_iterator<const_pointer, vector>   	const_iterator;
    typedef ft::reverse_iterator<iterator>           		reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     		const_reverse_iterator;


		// ====================================================== //
		// ================== Member functions ================== //
		// ====================================================== //

	public:

		// -- default constructor - //
		explicit vector(const allocator_type& __alloc = allocator_type()):
			 _alloc(__alloc), _start(NULL),  _end(NULL), _cap(NULL) {}

		//  constructor with 'size' and 'n' elemets to be filled  //
		explicit vector(size_type count, const value_type& value = value_type(),
	        const allocator_type& alloc = allocator_type()): 
			_alloc(alloc), _start(NULL), _end(NULL), _cap(NULL)
    	{
    	    if (count == 0)
    	        return;
    	    check_size(count);

    	    _start = _alloc.allocate(count);
    	    _cap = _start + count;
    	    _end = _cap;
    	    construct_range(_start, _end, value);
    	}

		//  constructor with other vector's iterators start and end  //
		    template <typename InputIt>
    	vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last,
           const allocator_type& alloc = allocator_type()):
		   	_alloc(alloc), _start(NULL), _end(NULL), _cap(NULL)
    	{
    	    typedef typename iterator_traits<InputIt>::iterator_category category;
    	    range_init(first, last, category());
   		}

		//  copy constructor, but needs testing  //
    	vector(const vector& other): _alloc(other._alloc),
    	      _start(NULL), _end(NULL), _cap(NULL)
    	{
    	    const size_type cap = other.capacity();
    	    if (cap == 0)
    	        return;
    	    _start = _alloc.allocate(cap);
    	    _cap = _start + cap;
    	    _end = construct_range(_start, other._start, other._end);
    	}

		// - assignment operator - //
		vector& operator=(const vector& other)
		{
			if (&other != this)
				assign(other.begin(), other.end());
			return *this;
		}
		// vector&	operator= (const vector& x)
		// {
		// 	if (*this != x)
		// 	{
		// 		clear();
		// 		reserve(x.capacity());
		// 		_size = x.size();
		// 		_alloc = x._alloc;
		// 		_capacity = x.capacity();
		// 		for (size_type i = 0; i < _size; ++i)
		// 			_alloc.construct(_start + i, x._start[i]);
		// 	}
		// 	return *this;
		// }

		// ------ destructor ------ //
		virtual ~vector() { deallocate_v(); }
		// ~vector()
		// {
		// 	--_end;
		// 	for (; _start != _end; --_end)
		// 	{
		// 		SHOW(_start + 1);
		// 		_alloc.destroy(_end);
		// 	}
		// 	if(capacity())
		// 		_alloc.deallocate(_start, capacity());
		// }
		// {
			
		// 	// this->clear();								// FIXME: Not sure if I need this
		// 	// this->_alloc.deallocate(_start, capacity());
		// 	for (iterator it = begin(); it != end(); ++it)
		// 		_alloc.destroy(&(*(it)));
		// 	_alloc.deallocate(_start, capacity());
		// }

		//  replaces the contents with copies of those in the range [first, last]  //
		template <typename InputIt>
		void assign(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)
		{
			typedef typename iterator_traits<InputIt>::iterator_category category;
			
			range_assign(first, last, category()); // 
		}

		//  replaces the contents with count copies of value value  //
		void assign(size_type count, const T& value)
		{
			if (count > capacity()) {
				vector tmp(count, value);
				tmp.swap(*this);
			} else if (count > size()) {
				std::fill(begin(), end(), value);
				const size_type extra = count - size();
				_end = construct_range(_end, _end + extra, value);
			} else {
				pointer it = std::fill_n(_start, count, value);
				erase_at_end(it);
			}
		}

		allocator_type get_allocator() const { return this->_alloc; }
		
		// template <class InputIterator>
		// void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		// {
		// 	clear();
		// 	difference_type __ns = std::distance(first, last);
		// 	if (__ns < 0)
		// 		throw("invalid range specified");
		// 	// std::assert(__ns >= 0, "invalid range specified");
		// 	const size_t __n = static_cast<size_type>(__ns);
		// 	if (__n)
		// 	{
		// 		if (__n > capacity())
		// 		{
		// 			// __vdeallocate();
		// 			deallocate_v();
		// 			_start = _alloc.allocate(__n);
		// 		}
		// 		// _end = _start;
		// 		for (size_type i = 0; i < __n; ++i, ++first)
		// 			_alloc.construct(_start + i, *first);
		// 		_end = _start + __n;
		// 		_cap = _end;
				
		// 		// __construct_at_end(__first, __last);
		// 	}
		// }
		// {
		// 	clear();
		// 	LOG("AGDSG")
		// 	for (; first != last; ++first)
		// 		push_back(*first);
		// }

		
		
	
		// ====================================================== //
		// ====================== Iterators ===================== //
		// ====================================================== //

		iterator				begin() 		{ return iterator(_start); }
		const_iterator			begin() const 	{ return const_iterator(_start); }
		iterator				end() 			{ return iterator(_end); }
		const_iterator			end() const 	{ return const_iterator(_end); }
		reverse_iterator		rbegin() 		{ return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const 	{ return const_reverse_iterator(end()); }
		reverse_iterator		rend() 			{ return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const 	{ return const_reverse_iterator(begin()); }
		
		// ====================================================== //
		// ====================== Capacity ====================== //
		// ====================================================== //

		size_type	size() const {  return static_cast<size_type>(_end - _start); }
		size_type	max_size() const { return std::min(_alloc.max_size(),
                        static_cast<size_type>(std::numeric_limits<difference_type>::max())); }				// FIXME: maybe need to change this part. I'll test later
		
		//  changes the _size; _size > __n ? _size = _n : allocate & fill with default value  //
		// void	resize(size_type __n, value_type __val = value_type())
		// {
		// 	if (_size == __n)
		// 		return;
		// 	if (__n > max_size())
		// 		throw std::out_of_range("ft::vector");
		// 	if (__n > _capacity)
		// 		insert(_start + _size, __n - _size, __val);
		// 	_size = __n;
		// }

		// void resize (size_type n, value_type val = value_type()){
		// 	if(n < _size){
		// 		for(size_type i = n; i < _size; i++)
		// 			_alloc.destroy(_start + i);
		// 		_size = n;
		// 	}
		// 	else if (n > _size){
		// 		if (_capacity < n)
		// 			this->reserve(_capacity * 2 > n ? _capacity * 2 : n);
		// 		for (size_type i = _size; i < n; i++){
		// 			_alloc.construct(_start + i, val);
		// 			_size++;
		// 		}
		// 	}
				
		// }

		void resize(size_type count, value_type value = value_type())
		{
			const size_type len = size();
			if (count > len) {
				insert(end(), count - len, value);
			} else if (count < len) {
				erase_at_end(_start + count);
			}
		}

		size_type	capacity() const	{ return static_cast<size_type>(_cap - _start); }
		bool		empty() const		{ return _start == _end; }

		//  reserves memory; __n < _capacity ? return : reallocate  //
		void reserve(size_type new_cap)
		{
			if (new_cap > capacity())
			{
				check_size(new_cap);

				pointer new_start = _alloc.allocate(new_cap);
				pointer new_end;

				new_end = construct_range(new_start, _start, _end);
				deallocate_v();
				_start = new_start;
				_end = new_end;
				_cap = _start + new_cap;
			}
		}


		// ====================================================== //
		// =================== Element access =================== //
		// ====================================================== //

		//  returns __n < _capacity ? __n-th element : type's default value (ex. for int – 0) //
		reference at(size_type pos)
		{
			range_check(pos);
			return (*this)[pos];
		}

		const_reference at(size_type pos) const
		{
			range_check(pos);
			return (*this)[pos];
		}

		reference operator[](size_type pos)
		{
			return *(_start + pos);
		}

		const_reference operator[](size_type pos) const
		{
			return *(_start + pos);
		}

		//  if we need first or last elements  //
		reference front()				{ return (*begin()); }
		const_reference front()	const	{ return (*begin()); }
		reference back()				{ return (*(end() - 1)); }
		const_reference back()	const	{ return (*(end() - 1)); }


		// ====================================================== //
		// ====================== Modifiers ===================== //
		// ====================================================== //

		//  appends the fiven element value to the end of the container  //
		void push_back(const value_type& value)
		{
			if (!should_grow()) {
				_alloc.construct(_end, value);
				++_end;
			} else {
				insert(end(), value);
			}
		}


		// void	push_back (const value_type& value)
		// { 
		// 	if (size() + 1 > capacity())
		// 		reserve(capacity() == 0 ? 1 : capacity() * 2);
		// 	_alloc.construct(_end, value);
		// 	++_end;
		// }

		//  removes the last element in the vector  //
		void pop_back(){
			--_end;
        	_alloc.destroy(_end);
		}
		
		//  inserts elements at the specified location in the container  //

		iterator insert(iterator pos, const value_type& value)
		{
			const size_type index = pos - begin();
			insert(pos, 1, value);
			return iterator(_start + index);
		}


		void insert(iterator pos, size_type count, const value_type& value)
		{
			if (count != 0) {
				const size_type extra_space = _cap - _end;

				if (extra_space >= count)
				{
					const size_type elems_after = end() - pos;
					pointer old_end = _end;
					if (elems_after > count)
					{
						_end = construct_range(_end, _end - count, _end);
						std::copy_backward(pos.base(), old_end - count, old_end);
						std::fill_n(pos, count, value);
					} else {
						_end = construct_range(_end, _end + (count - elems_after), value);
						_end = construct_range(_end, pos.base(), old_end);
						std::fill(pos.base(), old_end, value);
					}
				} else {
					const size_type new_size = calculate_growth(count);
					pointer new_start = _alloc.allocate(new_size);
					pointer new_end;

					new_end = construct_range(new_start, _start, pos.base());
					new_end = construct_range(new_end, new_end + count, value);
					new_end = construct_range(new_end, pos.base(), _end);
					
					deallocate_v();
					// for (size_type u = 0; u < this->size(); u++)
					// 	_alloc.destroy(_start + u);
					// _alloc.deallocate(_start, this->capacity());
					_start = new_start;
					_end = new_end;
					_cap = new_start + new_size;
				}
			}
		}



// void insert (iterator position, size_type n, const value_type& val)
// 			{
// 				pointer _end = _start + size() - 1;
// 				if (n == 0)
// 					return ;
// 				if (n > this->max_size())
// 					throw (std::length_error("vector::insert (fill)"));
// 				size_type pos_len = &(*position) - _start;
// 				if (size_type(_capacity - _end) >= n)
// 				{
// 					for (size_type i = 0; i < this->size() - pos_len; i++)
// 						_alloc.construct(_end - i + (n - 1), *(_end - i - 1));
// 					_end += n;
// 					while (n)
// 					{
// 						_alloc.construct(&(*position) + (n - 1), val);
// 						n--;
// 					}
// 				}
// 				else
// 				{
// 					pointer new_start = pointer();
// 					pointer new_end = pointer();
// 					pointer new__endcapacity = pointer();
					
// 					int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
// 					new_start = _alloc.allocate(next_capacity);
// 					new__endcapacity = new_start + next_capacity;

// 					if (size_type(new__endcapacity - new_start) < this->size() + n)
// 					{
// 						if (new_start)
// 							_alloc.deallocate(new_start, new_start - new__endcapacity);
// 						next_capacity = this->size() + n;
// 						new_start = _alloc.allocate(next_capacity);
// 						new_end = new_start + this->size() + n;
// 						new__endcapacity = new_start + next_capacity;
// 					}

					// new_end = new_start + this->size() + n;

					// for (int i = 0; i < (&(*position) - _start); i++)
					// 	_alloc.construct(new_start + i, *(_start + i));
					// for (size_type k = 0; k < n; k++)
					// 	_alloc.construct(new_start + pos_len + k, val);
			// 		for (size_type j = 0; j < (this->size() - pos_len); j++)
			// 			_alloc.construct(new_end - j - 1, *(_end - j - 1));

			// 		for (size_type u = 0; u < this->size(); u++)
			// 			_alloc.destroy(_start + u);
			// 		_alloc.deallocate(_start, this->capacity());

			// 		_start = new_start;
			// 		_end = new_end;
			// 		_capacity = new__endcapacity;
			// 	}
			// }

//			template <class InputIt>
//			void	insert(iterator pos, InputIt first,
//						   typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)


		//  inserts elements 'first'–'last' after position  //
		//   void insert(iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value,
//                                      InputIt>::type* = NULL) {
//     try {
//       InputIt s = first;
//       while (s < last) {
//         // value_type x = *s++;
// 		++s;
//       }
//     } catch (...) {
//       throw;
//     }
//     size_type count = static_cast<size_type>(std::distance(first, last));
//     if (count == 0) return;
//     size_type insertIdx = static_cast<size_type>(std::distance(begin(), pos));
//     if (size() + count > capacity()) {
//       int newCapacity =
//           capacity() * 2 >= size() + count ? capacity() * 2 : size() + count;
//       reserve(newCapacity);
//     }
//     if (empty()) {
//       assign(first, last);
//     } else {
//       for (size_type i = size() - 1; i >= insertIdx; --i) {
//         _alloc.construct(_start + i + count, _start[i]);
//         if (i == 0) break;
//       }
//       for (size_type i = 0; i < count; ++i) {
//         _alloc.construct(_start + insertIdx++, *first++);
//         _end++;
//       }
//     }
//   };
			// void insert(iterator position, InputIt begin, InputIt end)
			// {
			// 	while (first != last)
			// 	{
			// 		pos = insert(pos, *first) + 1;
			// 		++first;
			// 	}
			// }
			template <class InputIt>
		void insert(iterator pos, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last)

		{
			typedef typename iterator_traits<InputIt>::iterator_category category;
			range_insert(pos, first, last, category());
		}

		// template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
		// {
		// 	if (position < begin() || position > end() || first > last)
		// 		throw std::logic_error("vector");
		// 	size_type start = static_cast<size_type>(position - begin());
		// 	size_type count = static_cast<size_type>(last - first);
		// 	if (size() + count > capacity())
		// 	{
		// 			size_type new_cap = capacity() * 2 >= size() + count ? capacity() * 2 : size() + count;
		// 		pointer new_arr = _alloc.allocate(new_cap);
		// 		std::uninitialized_copy(begin(), position, iterator(new_arr));
		// 		try {
		// 			for (size_type i = 0; i < static_cast<size_type>(count); i++, first++)
		// 				_alloc.construct(new_arr + start + i, *first);
		// 		}
		// 		catch (...){
		// 			for (size_type i = 0; i < count + start; ++i)
		// 				_alloc.destroy(new_arr + i);
					// _alloc.deallocate(new_arr, new_cap);
		// 			throw;
		// 		}

		// 		std::uninitialized_copy(position, end(), iterator(new_arr + start + count));
		// 		for (size_type i = 0; i < size(); i++)
		// 			_alloc.destroy(_start + i);
		// 		_alloc.deallocate(_start, capacity());
		// 		_end += count;
		// 		_cap = _start + new_cap;
		// 		_start = new_arr;
		// 	}
		// 	else
		// 	{
		// 		for (size_type i = size(); i > static_cast<size_type>(start); i--) {
		// 			_alloc.destroy(_start + i + count - 1);
		// 			_alloc.construct(_start + i + count - 1, *(_start + i - 1));
		// 		}
		// 		for (size_type i = 0; i < static_cast<size_type>(count); i++, first++) {
		// 			_alloc.destroy(_start + i + count);
		// 			_alloc.construct(_start + start + i, *first);
		// 		}
		// 		_end += count;
		// 	}
		// }

		// iterator	erase (iterator position)
		// {
		// 	return	erase(position, position + 1);
		// }

		iterator erase(iterator pos) {
			size_type deletedIndex = static_cast<size_type>(std::distance(begin(), pos));
			_alloc.destroy(_start + deletedIndex);
    		for (size_type i = deletedIndex; i < size() - 1; ++i)
	  			_start[i] = _start[i + 1];
    		_end--;
			return iterator(_start + deletedIndex);
		}

		
		iterator erase(iterator first, iterator last)
		{
			if (first != last) {
				if (last != end()) {
					std::copy(last, end(), first);
				}
				pointer new_end = first.base() + (end() - last);
				erase_at_end(new_end);
			}
			return first;
		}


		inline void swap(vector& x)
		{
			std::swap(this->_start, x._start);
			std::swap(this->_end, x._end);
			std::swap(this->_cap, x._cap);
			std::swap(this->_alloc, x._alloc);
		}

		//  removes all elements from the vector and destroys em  //
		void	clear() { erase_at_end(_start); }

		
		// ====================================================== //
		// ===================== member data ==================== //
		// ====================================================== //
	private:
		allocator_type _alloc;
		pointer _start;
		pointer _end;
		pointer _cap;


		// ====================================================== //
		// ======================== utils ======================= //
		// ====================================================== //

		template <typename InputIt>
		void range_init(InputIt first, InputIt last, std::input_iterator_tag)
		{
			for (; first != last; ++first) {
				push_back(*first);
			}
		}

		template <typename ForwardIt>
		void range_init(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
		{
			const size_type count = std::distance(first, last);
			if (count == 0) {
				return;
			}
			check_size(count);

			_start = _alloc.allocate(count);
			_cap = _start + count;
			_end = construct_range(_start, first, last);
		}

		template <typename InputIt>
		void range_assign(InputIt first, InputIt last, std::input_iterator_tag)
		{
			clear();
			for (; first != last; ++first) {
				push_back(*first);
			}
		}

		template <typename ForwardIt>
		void range_assign(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
		{
			const size_type count = std::distance(first, last);
			if (count < size()) {
				iterator it = std::copy(first, last, begin());
				erase_at_end(it.base());
			} else {
				ForwardIt it = first;
				std::advance(it, size());
				std::copy(first, it, begin());
				insert(end(), it, last);
			}
		}

		
		// {
		// 	clear();
		// 	difference_type __ns = std::distance(first, last);
		// 	// if (__ns < 0)
		// 	// 	throw("invalid range specified");
		// 	// std::assert(__ns >= 0, "invalid range specified");
		// 	const size_t __n = static_cast<size_type>(__ns);
		// 	if (__n)
		// 	{
		// 		if (__n > capacity())
		// 		{
					// __vdeallocate();
		// 			deallocate_v();
		// 			_start = _alloc.allocate(__n);
		// 		}
		// 		if (__n < size()) {
		// 		// iterator it = std::copy(first, last, begin());
		// 		erase_at_end(_start + __n);
		// 		}
				
		// 		// _end = _start;
		// 		for (size_type i = 0; i < __n; ++i, ++first)
		// 			_alloc.construct(_start + i, *first);
		// 		_end = _start + __n;
		// 		_cap = _end;
				
		// 		// __construct_at_end(__first, __last);
		// 	}
		// }

		template <typename InputIt>
		void range_insert(iterator pos, InputIt first, InputIt last, std::input_iterator_tag)
		{
			if (pos == end()) {
				for (; first != last; ++first) {
					push_back(*first);
				}
			} else if (first != last) {
				vector tmp(first, last);
				insert(pos, tmp.begin(), tmp.end());
			}
		}

//    template <typename ForwardIt>
//     void range_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
// 	{
// 		size_type _size = size(), _capacity = capacity();
// 		// size_t range_size = last - first;
// 		size_t range_size = std::distance(first, last);
// 		if (!validate_iterator_values(first, last, range_size))
// 			throw std::exception();
// 		size_t new_size = size() + range_size;

// 		int last_index = (pos - begin()) + range_size - 1;
// 		if (range_size >= capacity()) {
// 			reserve(capacity() + range_size);
// 			_size = new_size;
// 		} else {
// 			while (_size != new_size) {
// 				if (_size == _capacity)
// 					reserve(_capacity * 2);
// 				_size++;
// 			}
// 		}
// 		for (int i = _size - 1; i >= 0; --i) {
// 			if (i == last_index) {
// 				for (; range_size > 0; --range_size, --i) {
// 					_start[i] = *--last;
// 				}
// 				return;
// 			}
// 			_start[i] = _start[i - range_size];
// 		}
// 		_end = _start + _size;
// 		_cap = _start + _capacity;
// 	};
	
protected:
	template<class InputIt>
	typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type
	validate_iterator_values(InputIt first, InputIt last, size_t range) {
		pointer reserved_buffer;
		reserved_buffer = _alloc.allocate(range);
		bool result = true;
		size_t i = 0;

		for (;first != last; ++first, ++i) {
			try { reserved_buffer[i] = *first; }
			catch (...) { result = false; break; }
		}
		_alloc.deallocate(reserved_buffer, range);
		return result;
	}
public:

   template <typename ForwardIt>
    void range_insert(iterator pos, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
    {
        if (first != last) {
            const size_type count = std::distance(first, last);
			if (!validate_iterator_values(first, last, count))
				throw std::exception();
            check_size(count);
            const size_type extra_space = _cap - _end;

            if (extra_space >= count) {
                const size_type elems_after = end() - pos;
                pointer old_end = _end;

                if (elems_after > count) {
                    _end = construct_range(_end, _end - count, _end);
                    std::copy_backward(pos.base(), old_end - count, old_end);
                    std::copy(first, last, pos);
                } else {
                    ForwardIt mid = first;
                    std::advance(mid, elems_after);
                    _end = construct_range(_end, mid, last);
                    _end = construct_range(_end, pos.base(), old_end);
                    std::copy(first, mid, pos);
                }
            } else {
                const size_type new_size = calculate_growth(count);
                pointer new_start = _alloc.allocate(new_size);
                pointer new_end = new_start;

				
                new_end = construct_range(new_start, _start, pos.base());
				pointer tmp = new_end;
                new_end = construct_range(new_end, first, last);
				new_end = construct_range(new_end, pos.base(), _end);
                deallocate_v();
                _start = new_start;
                _end = new_end;
                _cap = new_start + new_size;
            }
        }
    }

		bool should_grow() const
		{
			return _end == _cap;
		}

		void deallocate_v()
		{
			if (_start != NULL) {
				clear();
				_alloc.deallocate(_start, capacity());
			}
		}

		template <typename It>
		pointer construct_range(pointer dst, It start, It end)
		{
			for (; start != end; ++dst, (void)++start) {
				_alloc.construct(dst, *start);
			}
			return dst;
		}

		pointer construct_range(pointer dst, const_pointer end, const_reference value)
		{
			for (; dst != end; ++dst) {
				_alloc.construct(dst, value);
			}
			return dst;
		}

		void destroy_range(pointer start, pointer end)
		{
			for (; start != end; ++start) {
				_alloc.destroy(start);
			}
		}

		void erase_at_end(pointer pos)
		{
			destroy_range(pos, _end);
			_end = pos;
		}

		void length_exception() const
		{
			throw std::length_error("cannot create ft::vector larger than max_size()");
		}

		size_type calculate_growth(size_type extra) const
		{
			const size_type max = max_size();
			const size_type cap = capacity();
			if (max - cap < extra) {
				length_exception();
			}

			if (cap >= max / 2) {
				return max;
			}

			return std::max(size() + extra, cap * 2);
		}

		void check_size(size_type count)
		{
			if (count > max_size()) {
				length_exception();
			}
		}

		void range_check(size_type n) const
		{
			if (n >= size()) {
				std::stringstream ss;

				ss << "Index " << n << " is out of range (size = " << size();
				throw std::out_of_range(ss.str());
			}
		}


	};

	// ====================================================== //
	// ================ Non-Member overloads ================ //
	// ====================================================== //


	//  == != < > <= >= operator overloads  //

	// template <typename T, typename Alloc>
	// inline void swap(vector<T, Alloc>& __x, vector<T, Alloc>& __y)
	// {
	// 	__x.swap(__y);
	// }

	template <typename T, typename Alloc>
	inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, typename Alloc>
	inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Alloc>
	inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename Alloc>
	inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Alloc>
	inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Alloc>
	inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

}	// namespace ft

namespace std{
	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

# endif	// VECTOR_HPP
