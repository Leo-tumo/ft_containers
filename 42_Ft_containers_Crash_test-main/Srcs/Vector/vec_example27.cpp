/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_example27.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:37:51 by vismaily          #+#    #+#             */
/*   Updated: 2022/12/19 13:39:32 by vismaily         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Example 27 */
/* Example tests insert(fill) */

#include "test.hpp"

namespace	NS_TEST
{
	const std::string	vec_example27(double &_time)
	{
		std::ostringstream	ss;
		clock_t				start;
		clock_t				end;
		NS::vector<int>		vct;

		vct.assign(1000, 1);

		start = clock();
		vct.insert(vct.end() - 50, 42000000, 2);
		end = clock();
		_time = (double)(end - start);

		ss << " " << (vct[2121]);
		ss << " " << (vct.size());
		ss << " " << (vct.capacity());

		return (ss.str());
	}
}
