#include <iostream>
#include <vector>
# include <iterator>
#include <typeinfo>
#include <cstring>
#define LOG(x) std::cout << x << std::endl;
#define SHOW(...) std::cout << #__VA_ARGS__ << " ==== " << __VA_ARGS__ << std::endl;
#define MAIN_2

#ifdef MAIN_1
int main()
{
	std::vector<int> A;

	for (int i = 0; i < 1000; ++i)
	{
		A.push_back(i);
		std::cout << "size = " << A.size() << ";\tcapacity = " << A.capacity() << ";\tmax_size = " << A.max_size() << std::endl;
	}
	A.clear();
	std::cout << "size = " << A.size() << ";\tcapacity = " << A.capacity() << ";\tmax_size = " << A.max_size() << std::endl;
	std::sleep();
}
# else
#include <string>
int main()
{
	std::vector<int> vt(40, 7);
	vt.assign(4, 8);
	for (auto a: vt)
		std::cout << a << std::endl;
	LOG(vt.capacity());




}



# endif
