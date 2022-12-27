#include "vector.hpp"

int main()
{
	ft::vector<int> vt(7, 15);
	std::cout << vt[5];
	ft::vector<int>::iterator it = vt.end();
	SHOW(it - vt.begin());
}