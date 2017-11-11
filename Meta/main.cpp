#include <quantity.h>
#include <tiny.h>
#include <string>
#include <boost/mpl/size.hpp>
#include <boost/mpl/push_back.hpp>

int main(int argc, char* argv[]) {

	typedef meta::tiny<int, std::string, meta::na> ti;
	mpl::push_back<ti, int>::type a;
	static_assert(3 == mpl::size<decltype(a)>::type::value, "");
	 


	return 0;
}
