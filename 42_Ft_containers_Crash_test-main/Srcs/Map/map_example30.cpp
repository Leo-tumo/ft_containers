/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_example30.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vismaily <nenie_iri@mail.ru>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:24:35 by vismaily          #+#    #+#             */
/*   Updated: 2022/12/18 14:16:09 by tumolabs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Example 30 */
/* equal_range() */

#include "test.hpp"

namespace	NS_TEST
{
	const std::string	map_example30(double &_time)
	{
		std::ostringstream	ss;
		clock_t				start;
		clock_t				end;
		NS::map<int, int>	mp;

		mp.insert(NS::make_pair(10, 10));
		mp.insert(NS::make_pair(20, 20));
		mp.insert(NS::make_pair(30, 30));
		mp.insert(NS::make_pair(40, 40));
		mp.insert(NS::make_pair(50, 50));
		mp.insert(NS::make_pair(60, 60));

		start = clock();

		const NS::pair<NS::map<int, int>::const_iterator ,
		NS::map<int, int>::const_iterator>& pair = mp.equal_range(10);

		const NS::pair<NS::map<int, int>::const_iterator ,
		NS::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);

		const NS::pair<NS::map<int, int>::const_iterator ,
		NS::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);

		end = clock();
		_time = (double)(end - start);

		ss << " " << pair.first->first;
		ss << " " << pair.first->second;
		ss << " " << pair.second->first;
		ss << " " << pair.second->second;
		ss << " " << pair2.first->first;
		ss << " " << pair2.first->second;
		ss << " " << pair2.second->first;
		ss << " " << pair2.second->second;
		ss << " " << pair3.first->first;
		ss << " " << pair3.first->second;
		ss << " " << pair3.second->first;
		ss << " " << pair3.second->second;

		return (ss.str());
	}
}
