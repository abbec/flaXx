#include "math/montecarlo.h"

double flaXx::MonteCarlo::uniformPdf(double k, double a, double b)
{
	if (k > a && k < b)
		return 1/(b-a);
	else
		return 0.0;
}


double flaXx::MonteCarlo::getUniformNumber()
{
	return (rand()%100)/100;
}

