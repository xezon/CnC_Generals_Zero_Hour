/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2026 TheSuperHackers
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

#include "PreRTS.h"

#include "Common/Diagnostic/SimulationMathCrc.h"
#include "Common/XferCRC.h"
#include "WWMath/matrix3d.h"
#include "WWMath/wwmath.h"
#include "GameLogic/FPUControl.h"

#include <math.h>

static void appendSimulationMathCrc(XferCRC &xfer)
{
    Matrix3D matrix;
    Matrix3D factorsMatrix;

    matrix.Set(
        4.1f, 1.2f, 0.3f, 0.4f,
        0.5f, 3.6f, 0.7f, 0.8f,
        0.9f, 1.0f, 2.1f, 1.2f);

    factorsMatrix.Set(
        WWMath::Sin(0.7f) * log10f(2.3f),
        WWMath::Cos(1.1f) * powf(1.1f, 2.0f),
        WWMath::TanfOrigin(0.3f),
        WWMath::ASinfOrigin(0.967302263f),
        WWMath::ACosfOrigin(0.967302263f),
        WWMath::AtanfOrigin(0.967302263f) * WWMath::PowfOrigin(1.1f, 2.0f),
        WWMath::Atan2fOrigin(0.4f, 1.3f),
        WWMath::SinhfOrigin(0.2f),
        WWMath::CoshfOrigin(0.4f) * WWMath::TanhfOrigin(0.5f),
        WWMath::SqrtfOrigin(55788.84375f),
        WWMath::ExpfOrigin(0.1f) * WWMath::Log10fOrigin(2.3f),
        WWMath::LogfOrigin(1.4f));

    Matrix3D::Multiply(matrix, factorsMatrix, &matrix);
    matrix.Get_Inverse(matrix);

    xfer.xferMatrix3D(&matrix);
}

UnsignedInt SimulationMathCrc::calculate()
{
    XferCRC xfer;
    xfer.open("SimulationMathCrc");

    setFPMode();

    appendSimulationMathCrc(xfer);

    _fpreset();

    xfer.close();

    return xfer.getCRC();
}
