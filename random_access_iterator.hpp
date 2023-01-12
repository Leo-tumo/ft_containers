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
		random_access_iterator() : elem_(iterator_type()) {}

		explicit random_access_iterator(const iterator_type& it) : elem_(it) {}

		template <typename Iter>
		random_access_iterator(const random_access_iterator< Iter, typename enable_if<is_same<Iter, typename Container::pointer>::value,
												Container>::type>& it) : elem_(it.base()) {}

		~random_access_iterator(){};

		random_access_iterator& operator=(const random_access_iterator& other)
		{
			elem_ = other.elem_;
			return *this;
		}

	public:
		const iterator_type& base() const { return elem_; }

		reference operator*() const { return *elem_; }

		pointer operator->() const { return elem_; }

		random_access_iterator& operator++()
		{
			++elem_;
			return *this;
		}

		random_access_iterator operator++(int)
		{
			return random_access_iterator(elem_++);
		}

		random_access_iterator& operator--()
		{
			--elem_;
			return *this;
		}

		random_access_iterator operator--(int)
		{
			return random_access_iterator(elem_--);
		}

		reference operator[](difference_type n)
		{
			return *(elem_ + n);
		}

		random_access_iterator& operator+=(difference_type n)
		{
			elem_ += n;
			return *this;
		}

		random_access_iterator operator+(difference_type n) const
		{
			return random_access_iterator(elem_ + n);
		}

		random_access_iterator& operator-=(difference_type n)
		{
			elem_ -= n;
			return *this;
		}

		random_access_iterator operator-(difference_type n) const
		{
			return random_access_iterator(elem_ - n);
		}

	protected:
		pointer elem_;
	};

	template <typename L, typename R, typename Container>
	inline bool operator==(const random_access_iterator<L, Container>& lhs,
						const random_access_iterator<R, Container>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator==(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename L, typename R, typename Container>
	inline bool operator!=(const random_access_iterator<L, Container>& lhs,
						const random_access_iterator<R, Container>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator!=(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename ItL, typename ItR, typename Container>
	inline bool operator>(const random_access_iterator<ItL, Container>& lhs,
						const random_access_iterator<ItR, Container>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator>(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename ItL, typename ItR, typename Container>
	inline bool operator<(const random_access_iterator<ItL, Container>& lhs,
						const random_access_iterator<ItR, Container>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator<(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename ItL, typename ItR, typename Container>
	inline bool operator>=(const random_access_iterator<ItL, Container>& lhs,
						const random_access_iterator<ItR, Container>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator>=(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename ItL, typename ItR, typename Container>
	inline bool operator<=(const random_access_iterator<ItL, Container>& lhs,
						const random_access_iterator<ItR, Container>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename It, typename Container>
	inline bool operator<=(const random_access_iterator<It, Container>& lhs,
						const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename ItL, typename ItR, typename Container>
	inline typename random_access_iterator<ItL, Container>::difference_type
	operator-(const random_access_iterator<ItL, Container>& lhs, const random_access_iterator<ItR, Container>& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename Container>
	inline typename random_access_iterator<It, Container>::difference_type
	operator-(const random_access_iterator<It, Container>& lhs, const random_access_iterator<It, Container>& rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename Container>
	inline random_access_iterator<It, Container>
	operator+(typename random_access_iterator<It, Container>::difference_type n,
			const random_access_iterator<It, Container>& it)
	{
		return random_access_iterator<It, Container>(it.base() + n);
	}
} // namespace ft


#endif // RANDOM_ACCESS_ITERATOR_HPP
