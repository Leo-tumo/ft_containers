#include <iostream>
#include <vector>
# include <iterator>
#include <typeinfo>
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
	std::vector<std::string> kaka;
	kaka.push_back("hello");
	// kaka.push_back("vonc es");
	
	
	LOG("––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
	// for (auto a: kaka)
	// 	SHOW(a);
	kaka.clear();
	kaka.pop_back();
	// SHOW(kaka[1]);
	// SHOW(kaka.size());
	std::vector<int>::iterator it;




}



# endif
