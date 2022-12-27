// ********************************************************************** //
//                                                                        //
//             random_access_iterator.hpp                                 //
//             Created: 2022/12/22 18:24:11 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
#include "vector.hpp"
#include "util.h"

namespace ft {

template <class T>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

public:
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
	typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

protected:
	pointer _ptr;

public:
	// -- default constructor - //
	random_access_iterator(T *ptr = 0) : _ptr(ptr) {};
	// --- copy constructor --- //
	random_access_iterator(const random_access_iterator<T>& copy): _ptr(&(*copy)) {} /*  {this->_ptr = copy.getPtr();} */

	random_access_iterator operator= (const random_access_iterator<T>& rhs) 
	{
		// this->_ptr = copy.getPtr();
		_ptr = &(*rhs); 
		return *this;
	}

	virtual ~random_access_iterator() {}

	//  cast operator overload  //
	operator random_access_iterator<const T>() const
	{
		return this->_ptr;
	}

	//  pre-increment operator overload  //
	random_access_iterator& operator++ ()
	{
		++_ptr;
		return *this;
	}

	//  post-increment operator overload  //
	random_access_iterator& operator++ (int)
	{
		random_access_iterator tmp = *this;
		++_ptr;
		return tmp;
	}

	//  returns reference to the pointed element  //
	reference operator* () const
	{
		return *_ptr;
	}

	// ---- member access operator overload ---- //
	//  returns a pointer to the pointed element  //
	pointer operator-> () const
	{
		// return &(operator*());
		return _ptr;
	}

	//  pre-dicrement operator  //
	random_access_iterator	operator-- ()
	{
		--_ptr;
		return *this;
	}
	
	//  post-dicrement operator  //
	random_access_iterator	operator-- (int)
	{
		random_access_iterator tmp = *this;
		--(*this);
		return tmp;
	}

	//  returns an iterator +n steps away form current position  //
	random_access_iterator	operator+ (difference_type n) const
	{
		return random_access_iterator(this->_ptr + n);
	}

	//  returns an iterator -n steps away form current position  //
	random_access_iterator	operator- (difference_type n) const
	{
		return (_ptr - n);
	}

	//  move iterator n steps forward  //
	random_access_iterator	operator+= (difference_type n) 
	{
		_ptr += n;
		return *this;
	}

	//  move iterator n steps backward  //
	random_access_iterator	operator-= (difference_type n) 
	{
		_ptr -= n;
		return *this;
	}

	//  subscript operator overload  //
	reference	operator[] (difference_type n) const
	{
		// return _ptr[n];
		return *(_ptr + n);
	}

	//  give a pointer to the element where the iterator points  //
	pointer	base() const
	{
		return this->_ptr;
	}

	pointer	getPtr() const {
		return this->_ptr;
	} 

	bool operator==(const random_access_iterator& it) const    { return (it._ptr == _ptr); }
	bool operator!=(const random_access_iterator& it) const    { return (it._ptr != _ptr); }
	bool operator<(const random_access_iterator& it) const     { return (it._ptr > this->_ptr); }
	bool operator>(const random_access_iterator& it) const     { return (it._ptr < this->_ptr); }
	bool operator<=(const random_access_iterator& it) const    { return (it._ptr >= this->_ptr); }
	bool operator>=(const random_access_iterator& it) const    { return (it._ptr <= this->_ptr); }



// ====================================================== //
// ======= Relational operators ==, !=, >, <, etc. ====== //
// ====================================================== //
template <class L, class R>
friend bool	operator== (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class L, class R>
friend bool	operator!= (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class L, class R>
friend bool	operator< (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class L, class R>
friend bool	operator<= (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class L, class R>
friend bool	operator> (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class L, class R>
friend bool	operator>= (const random_access_iterator<L>& lhs,
					const random_access_iterator<R>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
friend random_access_iterator<Iterator>operator+(
	typename random_access_iterator<Iterator>::difference_type n,
	const random_access_iterator<Iterator>& iter) {
		return iter + n;
	}

template <class L, class R>
friend typename random_access_iterator<L>::difference_type	operator- (
		const random_access_iterator<L>& lhs,
		const random_access_iterator<R>& rhs) {
			return lhs.base() - rhs.base();
		}
};
} // namespace ft


#endif // RANDOM_ACCESS_ITERATOR_HPP
