#include "math/vector3f.h"
#include "math/montecarlo.h"

using namespace flaXx;

int main()
{

	MonteCarlo mc;

	mc.randomize();


	for (int i=0; i<10; i++)
		std::cout << mc.random() << std::endl;


	return 0;
}
