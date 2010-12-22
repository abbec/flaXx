#include "math/vector3f.h"
#include "math/montecarlo.h"
#include <cstdlib>
#include <ctime>
using namespace flaXx;

int main()
{
	srand(unsigned int(time(NULL)));

	for (int i=0; i<10; i++)
		std::cout << (rand() % 90 + 910)/1000.0 << std::endl;


	return 0;
}
