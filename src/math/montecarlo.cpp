#include "math/montecarlo.h"
#include <cstdlib>
#include <iostream>

double flaXx::MonteCarlo::uniformPdf(double k, double a, double b)
{
	return 1/(b-a);
}


double flaXx::MonteCarlo::getUniformNumber()
{
	return ((rand()%100)/100.0);
}

