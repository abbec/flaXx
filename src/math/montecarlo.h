/*
 * flaXx
 * Copyright (C) Albert Cervin <albert@nat0.se>, Nathalie Ek <nathalie@nat0.se> 2010
 * 
 * flaXx is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * flaXx is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	
	/** Function representing a uniform distribution  */
	double uniformPdf(double, double, double);

	/** Function returning a uniform number in the interval 0..1 */
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
