#ifndef MONTECARLO_H
#define MONTECARLO_H

namespace flaXx
{

class MonteCarlo
{
  public:
	MonteCarlo() {}
	
	/** Funktion som representerar en likformig fördelning  */
	double uniformPdf(double, double, double);

	/** Funktion som ger ett likformigt fördelat slumptal i intervallet 0..1 */
	double getUniformNumber();


};



} // end namespace flaXx
#endif // end MONTECARLO_H
