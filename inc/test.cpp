#include <iostream>
#include <vector>

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
	std::sleep()
}