// ********************************************************************** //
//                                                                        //
//             set.hpp                                                    //
//             Created: 2023/01/03 16:29:14 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef SET_HPP
#define SET_HPP

#include <memory>

#include "iterator.hpp"
#include "tree/__tree"

namespace ft
{
template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key> >
class set
{
public:
    typedef Key                                      key_type;
    typedef Key                                      value_type;
    typedef Compare                                  key_compare;
    typedef Compare                                  value_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::size_type       size_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

private:
    typedef tree<value_type, value_compare, Allocator> base;

public:
    typedef typename base::const_iterator              iterator;
    typedef typename base::const_iterator        const_iterator;
    typedef ft::reverse_iterator<iterator>       reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

// ====================================================== //
// ================== Member functions ================== //
// ====================================================== //

    set(): _tree(value_compare()) {}
    explicit set(const key_compare& comp, const allocator_type& alloc = allocator_type())
        : _tree(comp, alloc) {}

	template <class InputIt>
	set(InputIt first, InputIt last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()): _tree(comp, alloc) {
        insert(first, last);
    }
	set(const set& other) : _tree(other._tree) {}
    ~set() {}

	set&
	operator=(const set& other) {
		_tree = other._tree;
		return *this;
    }

	allocator_type
	get_allocator() const {
		return _tree.get_allocator();
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

	void
	clear() {
		_tree.clear();
	}

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
	swap(set& other) {
		_tree.swap(other._tree);
	}

// ====================================================== //
// ======================= Lookup ======================= //
// ====================================================== //

	size_type
	count(const key_type& key) const {
		return _tree.count(key);
	}

	iterator
	find(const key_type& key) {
		return _tree.find(key);
	}

	const_iterator
	find(const key_type& key) const {
		return _tree.find(key);
	}

	pair<iterator, iterator>
	equal_range(const key_type& key) {
		return _tree.equal_range(key);
	}

    pair<const_iterator, const_iterator>
	equal_range(const key_type& key) const {
		return _tree.equal_range(key);
	}

    iterator
	lower_bound(const key_type& key) {
		return _tree.lower_bound(key);
	}

    const_iterator
	lower_bound(const key_type& key) const {
		return _tree.lower_bound(key);
	}

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

	key_compare
	key_comp() const {
		return _tree.value_comp();
	}

    value_compare
	value_comp() const {
		return _tree.value_comp();
	}

private:
    base _tree;
};

template <typename Key, typename Compare, typename Allocator>
void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
{
    x.swap(y);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator==(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator!=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator<(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs)
{
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator<=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator>(const set<Key, Compare, Allocator>& lhs,
                      const set<Key, Compare, Allocator>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename Compare, typename Allocator>
inline bool operator>=(const set<Key, Compare, Allocator>& lhs,
                       const set<Key, Compare, Allocator>& rhs)
{
    return !(lhs < rhs);
}
} // namespace ft

#endif // SET_HPP
