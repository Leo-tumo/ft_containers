// ********************************************************************** //
//                                                                        //
//             random_access_iterator.hpp            		              //
//             Created: 2022/12/22 18:24:11 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include "iterator.hpp"

namespace ft
{
template <typename It, typename Container>
class random_access_iterator
{
public:
	typedef It                                              iterator_type;
	typedef typename iterator_traits<It>::iterator_category iterator_category;
	typedef typename iterator_traits<It>::value_type        value_type;
	typedef typename iterator_traits<It>::difference_type   difference_type;
	typedef typename iterator_traits<It>::reference         reference;
	typedef typename iterator_traits<It>::pointer           pointer;

public:
	random_access_iterator() : _ptr(iterator_type()) {}
	explicit random_access_iterator(const iterator_type& it) : _ptr(it) {}

	template <typename Iter>
	random_access_iterator(const random_access_iterator< Iter, typename enable_if<is_same<Iter,
		typename Container::pointer>::value, Container>::type>& it) : _ptr(it.base()) {}

	~random_access_iterator(){};

	random_access_iterator&
	operator=(const random_access_iterator& other) {
		_ptr = other._ptr;
		return *this;
	}

	const iterator_type& base() const { return _ptr; }

// ====================================================== //
// ==================== Overloads ... =================== //
// ====================================================== //

	reference operator*() const { return *_ptr; }
	pointer operator->() const { return _ptr; }

	random_access_iterator&
	operator++() {
		++_ptr;
		return *this;
	}

	random_access_iterator
	operator++(int) {
		return random_access_iterator(_ptr++);
	}

	random_access_iterator&
	operator--() {
		--_ptr;
		return *this;
	}

	random_access_iterator
	operator--(int) {
		return random_access_iterator(_ptr--);
	}

	reference
	operator[](difference_type n) {
		return *(_ptr + n);
	}

	random_access_iterator&
	operator+=(difference_type n) {
		_ptr += n;
		return *this;
	}

	random_access_iterator
	operator+(difference_type n) const {
		return random_access_iterator(_ptr + n);
	}

	random_access_iterator&
	operator-=(difference_type n) {
		_ptr -= n;
		return *this;
	}

	random_access_iterator
	operator-(difference_type n) const {
		return random_access_iterator(_ptr - n);
	}

protected:
	pointer _ptr;
};

template <typename L, typename R, typename Container>
inline bool
operator==(const random_access_iterator<L, Container>& lhs,
			const random_access_iterator<R, Container>& rhs) {
	return lhs.base() == rhs.base();
}

template <typename It, typename Container>
inline bool
operator==(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() == rhs.base();
}

template <typename L, typename R, typename Container>
inline bool
operator!=(const random_access_iterator<L, Container>& lhs,
			const random_access_iterator<R, Container>& rhs) {
	return lhs.base() != rhs.base();
}

template <typename It, typename Container>
inline bool
operator!=(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() != rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool
operator>(const random_access_iterator<ItL, Container>& lhs,
			const random_access_iterator<ItR, Container>& rhs) {
	return lhs.base() > rhs.base();
}

template <typename It, typename Container>
inline bool
operator>(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() > rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool
operator<(const random_access_iterator<ItL, Container>& lhs,
			const random_access_iterator<ItR, Container>& rhs) {
	return lhs.base() < rhs.base();
}

template <typename It, typename Container>
inline bool
operator<(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() < rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool
operator>=(const random_access_iterator<ItL, Container>& lhs,
			const random_access_iterator<ItR, Container>& rhs) {
	return lhs.base() >= rhs.base();
}

template <typename It, typename Container>
inline bool
operator>=(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() >= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline bool
operator<=(const random_access_iterator<ItL, Container>& lhs,
			const random_access_iterator<ItR, Container>& rhs) {
	return lhs.base() <= rhs.base();
}

template <typename It, typename Container>
inline bool
operator<=(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() <= rhs.base();
}

template <typename ItL, typename ItR, typename Container>
inline typename random_access_iterator<ItL, Container>::difference_type
operator-(const random_access_iterator<ItL, Container>& lhs,
			const random_access_iterator<ItR, Container>& rhs) {
	return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline typename random_access_iterator<It, Container>::difference_type
operator-(const random_access_iterator<It, Container>& lhs,
			const random_access_iterator<It, Container>& rhs) {
	return lhs.base() - rhs.base();
}

template <typename It, typename Container>
inline random_access_iterator<It, Container>
operator+(typename random_access_iterator<It, Container>::difference_type n,
		const random_access_iterator<It, Container>& it) {
	return random_access_iterator<It, Container>(it.base() + n);
}

} // namespace ft

#endif // RANDOM_ACCESS_ITERATOR_HPP
