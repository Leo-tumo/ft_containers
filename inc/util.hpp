// ********************************************************************** //
//                                                                        //
//             util.hpp   		       		                              //
//             Created: 2022/12/17 15:08:41 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef	UTIL_HPP
# define UTIL_HPP

#include "iterator.hpp"



namespace ft {

struct nullptr_t {
 private:
  void operator&() const;

 public:
  template < class T >
  inline operator T*() const {
    return 0;
  }

  template < class C, class T >
  inline operator T C::*() const {
    return 0;
  }
};
static nullptr_t u_nullptr = {};
// namespace ft{
# include "iterator.hpp"
template < class InputIterator >
typename ft::iterator_traits< InputIterator >::difference_type difference(
    InputIterator first, InputIterator last) {
	typedef typename ft::iterator_traits< InputIterator >::difference_type size_type;
	size_type n = 0;
	for (; first != last; ++first) {
		++n;
	}
  	return n;
	}
}



# endif // VECTOR_ITERATOR_HPP
