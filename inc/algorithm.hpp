// ********************************************************************** //
//                                                                        //
//             algorithm.hpp                                              //
//             Created: 2022/12/17 16:48:20 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

namespace ft {

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	for (; first1 != last1; ++first1, (void)++first2)
		if (!(*first1 == *first2))
			return false;
	return true;
}

//  if == operator is not overload, we must use predicate  //
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
	for (; first1 != last1; ++first1, (void)++first2)
		if (!bool(pred(*first1,*first2)))
			return false;
	return true;
}

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2) {
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp) {
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first2, *first1))
			return false;
		else if (comp(*first1, *first2))
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

} // namespace ft

#endif // ALGORITHM_HPP
