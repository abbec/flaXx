#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <ctime>
#include "math/vector3f.h"

namespace flaXx
{

/* Period parameters */  
#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

class MonteCarlo
{
  public:
	MonteCarlo();
	
	/** Funktion som representerar en likformig fördelning  */
	double uniformPdf(double, double, double);

	/** Funktion som ger ett likformigt fördelat slumptal i intervallet 0..1 */
	double getUniformNumber();

	Vector3f getCosineLobeDir();

	double cosineLobePdf(Vector3f psi, Vector3f Nx) { return ((psi*Nx)/M_PI); }

	/** Returns a random double between 0-1 */
	double random();
	/** Returns a random number between 0 and n-1. It is
	 * an implementation of a Mersenne Twister pseudorandom 
	 * number generator. */
	unsigned int random(unsigned int n);


	void setRandomSeed(unsigned int n);
	unsigned int getRandomSeed(void) { return rseed; }
	void randomize(void) { setRandomSeed((unsigned int)time(NULL)); }

  private:

	// Data
	unsigned int		rseed;
	unsigned int		rseed_sp;
	unsigned long mt[CMATH_N]; // The array for the state vector
	int mti; //  mti==N+1 means mt[N] is not initialized

};



} // end namespace flaXx
#endif // end MONTECARLO_H
