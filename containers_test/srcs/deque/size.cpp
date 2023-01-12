#include "common.hpp"

#define TESTED_TYPE int

void	is_empty(TESTED_NAMESPACE::deque<TESTED_TYPE> const &deq)
{
	std::cout << "is_empty: " << deq.empty() << std::endl;
}

int		main(void)
{
	const int _startsize = 7;
	TESTED_NAMESPACE::deque<TESTED_TYPE> deq(_startsize, 20);
	TESTED_NAMESPACE::deque<TESTED_TYPE> deq2;
	TESTED_NAMESPACE::deque<TESTED_TYPE>::iterator it = deq.begin();

	for (int i = 2; i < _startsize; ++i)
		it[i] = (_startsize - i) * 3;
	printSize(deq, true);

	deq.resize(10, 42);
	printSize(deq, true);

	deq.resize(18, 43);
	printSize(deq, true);
	deq.resize(10);
	printSize(deq, true);
	deq.resize(23, 44);
	printSize(deq, true);
	deq.resize(5);
	printSize(deq, true);
	deq.resize(87);
	deq.resize(5);
	printSize(deq, true);

	is_empty(deq2);
	deq2 = deq;
	is_empty(deq2);
	printSize(deq, true);
	printSize(deq2, true);

	deq2.resize(0);
	is_empty(deq2);
	printSize(deq2, true);
	return (0);
}
