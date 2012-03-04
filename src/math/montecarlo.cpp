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

#include "math/montecarlo.h"
#include <cstdlib>
#include <iostream>

using namespace flaXx;


MonteCarlo::MonteCarlo()
{
	rseed = 1;
	// safe0 start
	rseed_sp = 0;
	mti=CMATH_N+1;
	// safe0 end
}

double MonteCarlo::uniformPdf(double k, double a, double b)
{
	return 1/(b-a);
}


double MonteCarlo::getUniformNumber()
{
	return ((rand()%100)/100.0);
}

// NOT USED!
Vector3f MonteCarlo::getCosineLobeDir()
{
	// Generate point on hemisphere (cosine sampling)
	double r1 = rand() / ((double)RAND_MAX + 1);
	double phi = r1 * M_PI * 2.0;
	double r2 = rand() / ((double)RAND_MAX + 1);
	double theta = acos(sqrt(r2));

	double xDir = cos(phi) * sin(theta);
	double yDir = sin(phi) * sin(theta);
	double zDir = cos(theta);

	return Vector3f(xDir, yDir, zDir);

}

// Mersenne-Twister random number generator
unsigned int MonteCarlo::random(unsigned int n)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0, CMATH_MATRIX_A};

	if(n==0)
		return(0);

    if (mti >= CMATH_N) 
	{ 
		/* generate N words at one time */
        int kk;

        if (mti == CMATH_N+1)   /* if sgenrand() has not been called, */
            setRandomSeed(4357); /* a default initial seed is used   */

        for (kk=0;kk<CMATH_N-CMATH_M;kk++) 
		{
            y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
            mt[kk] = mt[kk+CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        
		for (;kk<CMATH_N-1;kk++) 
		{
            y = (mt[kk]&CMATH_UPPER_MASK)|(mt[kk+1]&CMATH_LOWER_MASK);
            mt[kk] = mt[kk+(CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        y = (mt[CMATH_N-1]&CMATH_UPPER_MASK)|(mt[0]&CMATH_LOWER_MASK);
        mt[CMATH_N-1] = mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

        mti = 0;
    }
  
    y = mt[mti++];
    y ^= CMATH_TEMPERING_SHIFT_U(y);
    y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
    y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
    y ^= CMATH_TEMPERING_SHIFT_L(y);

	// ET - old engine added one to the result.
	// We almost NEVER wanted to use this function
	// like this.  So, removed the +1 to return a 
	// range from 0 to n (not including n).
    return (y%n);
}



double MonteCarlo::random()
{
	int r = (int)random(0xffffffff);
	float divisor = (float)0xffffffff;
	return (r / divisor) + 0.5f;
}


void MonteCarlo::setRandomSeed(unsigned int n)
{
	mt[0]= n & 0xffffffff;

	for (mti=1; mti<CMATH_N; mti++)
		mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

	rseed = n;
}
