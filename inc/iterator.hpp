// ********************************************************************** //
//                                                                        //
//             iterator.hpp                                               //
//             Created: 2022/12/17 15:17:20 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include <iostream>

namespace ft{

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
	template < class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T& >
	
	struct iterator {
		
		typedef Category	iterator_category;
		typedef	T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef	Reference	reference;
	};

	template < class Iterator >
	struct iterator_traits {
		
		typedef typename Iterator::iterator_category 	iterator_category;
		typedef typename Iterator::value_type 			value_type;
		typedef typename Iterator::difference_type 		difference_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference			reference;
	};

	template < class T >
	struct iterator_traits< T* > {
		typedef	random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	T*							pointer;
		typedef T&							reference;
	};

	template < class T >
	struct iterator_traits< T* const > {
		typedef	random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	const T*					pointer;
		typedef const T&					reference;
	};

	template < class Iterator >
	class reverse_iterator {
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type 			value_type;
		typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
		typedef typename iterator_traits<Iterator>::pointer 			pointer;
		typedef typename iterator_traits<Iterator>::reference 			reference;
	
	protected:
		iterator_type	current;
	
	public:
		reverse_iterator() : current(){};
		explicit reverse_iterator(iterator_type it) : current(it) {};

		template < class Iter >
		reverse_iterator(const reverse_iterator< Iter >& rev_it) : current(rev_it.base()) {};

		virtual ~reverse_iterator(){};

		iterator_type	base() const { return current; }

		operator	reverse_iterator< const Iterator >() const { return this->current; }
		
		reference	operator* () const {
			iterator_type tmp = current;
			return *(--tmp);
		}

		reverse_iterator operator+ (difference_type n) const {
			return reverse_iterator(current - n);
		}

		reverse_iterator& operator++ () {
			--current;
			return *this;
		}

		reverse_iterator operator++ (int) {
			reverse_iterator	tmp(*this);
			--current;
			return tmp;
		}

		reverse_iterator& operator +=(difference_type n) {
			current -= n;
			return *this;
		}

		reverse_iterator operator- (difference_type n) const {
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator--() {
			++current;
			return *this;
		}

		reverse_iterator operator-- (int) {
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}

		reverse_iterator& operator -=(difference_type n) {
			current += n;
			return *this;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reference	operator[](difference_type n) const {
			return (current[-n -1]);
		}
	};
	
	template < class Iterator1, class Iterator2 >
	bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template < class Iterator1, class Iterator2 >
	bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template < class Iterator >
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it){
			return	rev_it + n;
	}

	template < class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
			return rhs.base() - lhs.base();
	}



} // namespace ft

#endif // ITERATOR_HPP
