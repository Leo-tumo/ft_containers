// ********************************************************************** //
//                                                                        //
//             type_traits.hpp                                            //
//             Created: 2022/12/17 16:32:00 by leo                        //
//             Made by: leo <leonidas.xaralambos@gmail.com>               //
//                                                                        //
// ********************************************************************** //

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft{

	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	template <typename T, T v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;

		operator value_type() const { return value; }

		value_type operator()() const { return value; }
	};

	typedef ft::integral_constant<bool, true>	true_type;
	typedef ft::integral_constant<bool, false>	false_type;

	template <typename T>
	struct remove_const { typedef T type; };

	template <typename T>
	struct remove_const<const T> { typedef T type; };

	template <typename T>
	struct remove_volatile { typedef T type; };

	template <typename T>
	struct remove_volatile<volatile T> { typedef T type; };

	template <class T> struct  remove_reference        {typedef  T type;};

	template <class T> struct  remove_reference<T&>  {typedef  T type;};
	
	template <typename T>
	struct remove_cv {
		typedef typename remove_volatile<typename remove_const<T>::type>::type type;
	};
	template <class T>
	struct __uncvref  {
    typedef typename remove_cv<typename remove_reference<T>::type>::type type;
	};

	template <typename>
	struct is_integral_base : public false_type {};
	template <>
	struct is_integral_base<bool> : public true_type {};
	template <>
	struct is_integral_base<char> : public true_type {};
	template <>
	struct is_integral_base<signed char> : public true_type {};
	template <>
	struct is_integral_base<short int> : public true_type {};
	template <>
	struct is_integral_base<int> : public true_type {};
	template <>
	struct is_integral_base<long int> : public true_type {};
	template <>
	struct is_integral_base<unsigned char> : public true_type {};
	template <>
	struct is_integral_base<unsigned short int> : public true_type {};
	template <>
	struct is_integral_base<unsigned int> : public true_type {};
	template <>
	struct is_integral_base<unsigned long int> : public true_type {};
	template <>
	struct is_integral_base<wchar_t> : public true_type {};
	template <>
	struct is_integral_base<char16_t> : public true_type {};
	template <>
	struct is_integral_base<unsigned long long> : public true_type {};
	template <>
	struct is_integral_base<long long> : public true_type {};
	template <typename T>
	struct is_integral : is_integral_base<typename remove_cv<T>::type> {};
	
	template <typename T, typename U>
	struct is_same : public false_type {};
	template <typename T>
	struct is_same<T, T> : public true_type {};

} // namespace ft


#endif // TYPE_TRAITS_HPP
