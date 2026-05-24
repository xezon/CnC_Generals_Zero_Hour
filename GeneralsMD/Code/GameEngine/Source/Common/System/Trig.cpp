/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// Trig.cpp
// fast trig functions
// Author: Michael S. Booth, March 1994
// Converted to Generals by Matthew D. Campbell, February 2002

#include "PreRTS.h"

#include "Lib/BaseType.h"
#include "Lib/trig.h"

#if USE_DETERMINISTIC_MATH
#include "gmath.h"
#endif

#if USE_DETERMINISTIC_MATH
Real Sin(Real x) { return gm_sinf(x); }
Real Cos(Real x) { return gm_cosf(x); }
Real Tan(Real x) { return gm_tanf(x); }
Real ACos(Real x) { return gm_acosf(x); }
Real ASin(Real x) { return gm_asinf(x); }
Real Sqrt(Real x) { return gm_sqrtf(x); }
double Sqrt(double x) { return gm_sqrt(x); }
#else
Real Sin(Real x) { return sinf(x); }
Real Cos(Real x) { return cosf(x); }
Real Tan(Real x) { return tanf(x); }
Real ACos(Real x) { return acosf(x); }
Real ASin(Real x) { return asinf(x); }
Real Sqrt(Real x) { return (Real)sqrt((double)x); }
double Sqrt(double x) { return sqrt(x); }
#endif
