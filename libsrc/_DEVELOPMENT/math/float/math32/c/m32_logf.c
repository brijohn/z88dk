/* Natural logarithm
 *
 * SYNOPSIS:
 *
 * float x, y, logf();
 *
 * y = logf( x );
 *
 *
 * DESCRIPTION:
 *
 * Returns the base e (2.718...) logarithm of x.
 *
 * The argument is separated into its exponent and fractional
 * parts.  If the exponent is between -1 and +1, the logarithm
 * of the fraction is approximated by
 *
 *     log(1+x) = x - 0.5 x**2 + x**3 P(x)
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0.5, 2.0    100000       7.6e-8     2.7e-8
 *    IEEE      1, MAXNUMF  100000                  2.6e-8
 *
 * In the tests over the interval [1, MAXNUM], the logarithms
 * of the random arguments were uniformly distributed over
 * [0, MAXLOGF].
 *
 * ERROR MESSAGES:
 *
 * logf singularity:  x = 0; returns MINLOG
 * logf domain:       x < 0; returns MINLOG
 */

/*
 * Cephes Math Library Release 2.2:  June, 1992
 * Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
 * Direct inquiries to 30 Frost Street, Cambridge, MA 02140
 */
 
/* Single precision natural logarithm
 * test interval: [sqrt(2)/2, sqrt(2)]
 * trials: 10000
 * peak relative error: 7.1e-8
 * rms relative error: 2.7e-8
 */
 
#include "m32_math.h"

#define MINLOGF -88.7228391116729996
#define SQRTHF 0.707106781186547524

extern float m32_coeff_log[];

float m32_logf (float x) __z88dk_fastcall
{
    float y, z, floate;
    int8_t e;

    if( x <= 0.0 )
    {
        return( MINLOGF );
    }
     
    x = m32_frexpf( x, &e );
    
    if( x < SQRTHF )
    {
        e -= 1;
        x = x + x - 1.0; /*  2x - 1  */
    }   
    else
    {
        x = x - 1.0;
    }
    
    z = m32_sqrf(x);

    y = m32_polyf(x, m32_coeff_log, 9) * z;
 
    if( e != 0)
    {
        floate = (float)e;
        y += -2.12194440e-4 * floate;
    }
     
    y +=  -0.5 * z; /* y - 0.5 x^2 */
    z = x + y;      /* ... + x  */
     
    if( e != 0)
    {
        z += 0.693359375 * floate;
    }
     
    return( z );
}
