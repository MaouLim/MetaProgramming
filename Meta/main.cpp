#include <quantity.h>

int main(int argc, char* argv[]) {

	meta::quantity<double, meta::mass>         m(1.0);
	meta::quantity<double, meta::acceleration> a(2.0);

	meta::quantity<double, meta::force> f = m * a;
}
