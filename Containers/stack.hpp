// ********************************************************************** //
//                                                                        //
//             stack.hpp                                                  //
//             Created: 2023/01/12 16:27:44 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft
{
template <typename T, typename Container = vector<T> >
class stack
{
public:
    typedef Container									container_type;
    typedef typename container_type::value_type			value_type;
    typedef typename container_type::size_type			size_type;
    typedef typename container_type::reference			reference;
    typedef typename container_type::const_reference	const_reference;

public:

// ====================================================== //
// ================== Member functions ================== //
// ====================================================== //

    explicit stack(const container_type& cont = container_type()) : c(cont) {}
    stack(const stack& other) : c(other.c) {}
    ~stack() {}
    stack&
	operator= (const stack& other) {
        c = other.c;
        return *this;
    }

// ====================================================== //
// =================== Element access =================== //
// ====================================================== //

	//  accesses the top element  // 
    reference top() { return c.back(); }
    const_reference top() const { return c.back();}

// ====================================================== //
// ====================== Capacity ====================== //
// ====================================================== //
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }

// ====================================================== //
// ====================== Modifiers ===================== //
// ====================================================== //

    void push(const value_type& value) { c.push_back(value); }
    void pop() { c.pop_back(); }

    template <typename T1, typename C1>
    friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

    template <typename T1, typename C1>
    friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

protected:
    container_type c;
};

template <typename T, typename Container>
inline bool
operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c == rhs.c;
}

template <typename T, typename Container>
inline bool
operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Container>
inline bool
operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c < rhs.c;
}

template <typename T, typename Container>
inline bool
operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(rhs < lhs);
}

template <typename T, typename Container>
inline bool
operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return rhs < lhs;
}

template <typename T, typename Container>
inline bool
operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs < rhs);
}
} // namespace ft

#endif // STACK_HPP
