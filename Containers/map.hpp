// ********************************************************************** //
//                                                                        //
//             map.hpp                                                    //
//             Created: 2023/01/10 18:24:28 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //


#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "iterator.hpp"
#include "tree/__tree"

namespace ft
{

template < typename Key, typename T, typename Compare >
class map_value_compare : public std::binary_function<Key, Key, bool>
{
public:
	typedef	Key		first_argument_type;
	typedef	Key		second_argument_type;
	typedef bool	result_type;

	map_value_compare() : _comp() {}
	map_value_compare(const Compare& cmp) : _comp(cmp)  {}

	const Compare&
	key_comp() const {
		return _comp;
	}

	bool
	operator() (const T& a, const T& b) const {
        return key_comp()(a.first, b.first);
    }

	bool
	operator() (const Key& a, const T& b) const {
		return key_comp()(a, b.first);
	}

	bool
	operator() (const T& a, const Key& b) const {
		return key_comp()(a.first, b);
	}

	void
	swap(map_value_compare& x) {
		std::swap(_comp, x._comp);
	}

protected:
	Compare	_comp;
};

template <typename Key, typename T, typename Compare>
void swap(map_value_compare<Key, T, Compare>& x, map_value_compare<Key, T, Compare>& y)
{
    x.swap(y);
}

template <typename Key, typename T, typename Compare = std::less<Key>,
			typename Allocator = std::allocator<pair<const Key, T> > >
class map
{
public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

private:
	typedef map_value_compare<key_type, value_type, key_compare>	vt_compare;
	typedef tree<value_type, vt_compare, allocator_type>			base;

public:
	typedef typename base::iterator					iterator;
	typedef typename base::const_iterator			const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

// ====================================================== //
// ==================== nested class ==================== //
// ====================================================== //
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	
	public:
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		typedef bool result_type;

		bool
		operator() (const value_type& a, const value_type& b) const {
			return comp(a.first, b.first);
		}

	protected:
		value_compare(const key_compare& c): comp(c) {}

		key_compare	comp;	
	};
public:
// ====================================================== //
// ================== Member functions ================== //
// ====================================================== //
	map(): _tree(vt_compare()) {}
	explicit map(const key_compare& comp, const allocator_type&alloc = allocator_type())
			: _tree(vt_compare(comp), alloc) {}
	template <typename InputIt>
	map(InputIt first, InputIt last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()): _tree(vt_compare(comp), alloc){
			insert(first, last);
		}
	map(const map& other): _tree(other._tree) {}

	map&
	operator= (const map& rhs){
		_tree = rhs._tree;
		return *this;
	}
	~map() {}

	allocator_type
	get_allocator() const {
		return _tree.get_allocator();
	}

// ====================================================== //
// =================== Element access =================== //
// ====================================================== //

	//  access specified element with bounds checking  // 
	T&
	at(const key_type& key) {
        iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

    const T&
	at(const key_type& key) const {
        const_iterator it = find(key);
        if (it == end()) {
            throw std::out_of_range("Key not found");
        }
        return it->second;
    }

	//  access or insert specified element  //
    T&
	operator[](const key_type& key) {
        return insert(ft::make_pair(key, T())).first->second;
    }

// ====================================================== //
// ====================== Iterators ===================== //
// ====================================================== //

	iterator begin() { return _tree.begin(); }
    const_iterator begin() const { return _tree.begin(); }
    iterator end() { return _tree.end(); }
    const_iterator end() const { return _tree.end(); }
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

// ====================================================== //
// ====================== Capacity ====================== //
// ====================================================== //

	bool empty() const { return _tree.empty(); }
    size_type size() const { return _tree.size(); }
    size_type max_size() const { return _tree.max_size(); }

// ====================================================== //
// ====================== Modifiers ===================== //
// ====================================================== //

	void clear() { _tree.clear(); }

	// --- inserts elements --- //
    pair<iterator, bool>
	insert(const value_type& value) {
        return _tree.insert(value);
    }

    iterator
	insert(iterator hint, const value_type& value) {
        return _tree.insert(hint, value);
    }

    template <typename InputIt>
    void
	insert(InputIt first, InputIt last) {
        _tree.insert(first, last);
    }

    void
	erase(iterator pos) {
        _tree.erase(const_iterator(pos));
    }

    void
	erase(iterator first, iterator last) {
        _tree.erase(first, last);
    }

    size_type
	erase(const key_type& key) {
        return _tree.erase(key);
    }

    void
	swap(map& other) {
        _tree.swap(other._tree);
    }

// ====================================================== //
// ======================= Lookup ======================= //
// ====================================================== //

	//  returns the number of elements matching specific key  //
	size_type
	count(const key_type& key) const {
		return _tree.count(key);
	}

	//  finds element with specific key  //
	iterator
	find(const key_type& key) {
		return _tree.find(key);
	}

	const_iterator
	find(const key_type& key) const {
		return _tree.find(key);
	}

	//  returns range of elements matching a specific key  //
	pair<iterator, iterator>
	equal_range(const key_type& key) {
		return _tree.equal_range(key);
	}

	pair<const_iterator, const_iterator>
	equal_range(const key_type& key) const {
        return _tree.equal_range(key);
    }

	//  returns an iterator to the first element not less than the given key  //
    iterator
	lower_bound(const key_type& key) {
        return _tree.lower_bound(key);
    }

    const_iterator
	lower_bound(const key_type& key) const {
        return _tree.lower_bound(key);
    }

	//  returns an iterator to the first element greater than the given key  //
    iterator
	upper_bound(const key_type& key) {
        return _tree.upper_bound(key);
    }

    const_iterator
	upper_bound(const key_type& key) const {
        return _tree.upper_bound(key);
    }

// ====================================================== //
// ====================== Observers ===================== //
// ====================================================== //

	//  returns the function that compares keys  //
    key_compare
	key_comp() const {
        return _tree.value_comp().key_comp();
    }

	//  returns the function that compares keys in objects of type value_type  //
    value_compare
	value_comp() const {
        return value_compare(_tree.value_comp().key_comp());
    }

private:
	base	_tree;
};

template <typename Key, typename T, typename Compare, typename Allocator>
inline void
swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y) {
    x.swap(y);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator==(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
	return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

// ##################################################################### //
// ########## lexicographically compares the values in the map ######### //
// ##################################################################### //

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator!=(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
	return !(lhs == rhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator<(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator<=(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
    return !(rhs < lhs);
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator>(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
    return rhs < lhs;
}

template <typename Key, typename T, typename Compare, typename Allocator>
inline bool
operator>=(const map<Key, T, Compare, Allocator>& lhs,
			const map<Key, T, Compare, Allocator>& rhs) {
    return !(lhs < rhs);
}

} // namespace ft

#endif // MAP_HPP