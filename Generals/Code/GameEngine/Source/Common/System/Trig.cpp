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
//																			  //
//  (c) 2001-2003 Electronic Arts Inc.										  //
//																			  //
////////////////////////////////////////////////////////////////////////////////

// Trig.cpp
// TheSuperHackers @refactor Redirect legacy trig functions to deterministic WWMath wrappers.
// Original implementations called CRT float functions (sinf, cosf, acosf, asinf, tanf).

#include "PreRTS.h"

#include "Lib/BaseType.h"
#include "Lib/trig.h"
#include "WWMath/wwmath.h"

Real Sin(Real x)
{
	return WWMath::SinTrig(x);
}

Real Cos(Real x)
{
	return WWMath::CosTrig(x);
}

Real Tan(Real x)
{
	return WWMath::TanTrig(x);
}

Real ACos(Real x)
{
	return WWMath::ACosTrig(x);
}

Real ASin(Real x)
{
	return WWMath::ASinTrig(x);
}
