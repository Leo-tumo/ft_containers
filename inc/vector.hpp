// ********************************************************************** //
//                                                                        //
//             vector.hpp                                                 //
//             Created: 2022/12/06 23:04:53 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>

namespace ft {
template <typename T, class Allocator = std::allocator<T> >
class Vector {
public:
	typedef Allocator allocator_type;
	typedef T value_type;
	/* value_type& */
	typedef typename allocator_type::reference reference;
	/* const value_type& */
	typedef typename allocator_type::const_reference const_reference;
	/* value_type* */
	typedef typename allocator_type::pointer pointer;
	/* const value_type* */
	typedef typename allocator_type::const_pointer const_pointer;

	/* iterator */
	typedef  iterator;
	/* const iterator */
	typedef  const_iterator;
	/* reverse iterator */
	typedef typename  reverse_iterator; // TODO:
	/* const reverse iterator */
	typedef typename const_reverse_iterator; // TODO:
	/* difference_type aka signed integral type */
	typedef typename allocator_type::difference_type;
	/* size_type aka unsigned integral type */
	typedef typename allocator_type::size_type size_type;



	
	Vector();

private:
	T*		_arr;
	size_t	_capacity;
	size_t	_size;

};

} // namespace ft





# endif // VECTOR_HPP
