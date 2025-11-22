/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 TheSuperHackers
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

#include "W3DDevice/Common/W3DCameraUtility.h"

#include "W3DDevice/Common/W3DConvert.h"

#include "vector2.h"
#include "vector3.h"
#include "camera.h"


void W3DPickRayPos(
	Vector3 &outRayStart,
	Vector3 &outRayEnd,
	const CameraClass &camera,
	const Vector2 &viewPoint)
{
	Vector3 rayDir;
	W3DPickRayDir(outRayStart, rayDir, camera, viewPoint);
	rayDir *= camera.Get_Depth(); //adjust length to reach far clip plane
	outRayEnd = outRayStart + rayDir; //get point on far clip plane along ray from camera
}

void W3DPickRayDir(
	Vector3 &outRayStart,
	Vector3 &outRayDir,
	const CameraClass &camera,
	const Vector2 &viewPoint)
{
	outRayStart = camera.Get_Position(); //get camera location
	camera.Un_Project(outRayDir, viewPoint); //get world space point
	outRayDir -= outRayStart; //vector camera to world space point
	outRayDir.Normalize(); //make unit vector
}

bool W3DViewPointToWorldAtZ(
	Coord3D &outWorldPos,
	const CameraClass &camera,
	const Vector2 &viewPoint,
	Real z,
	bool allowMirror)
{
	Vector3 rayStart;
	Vector3 rayEnd;
	W3DPickRayPos(rayStart, rayEnd, camera, viewPoint);

#if 0
	// this seems wrong?
	if ((z < rayStart.Z && rayStart.Z < rayEnd.Z)
		|| (z > rayStart.Z && rayStart.Z > rayEnd.Z))
	{
		if (!allowMirror)
		{
			return false;
		}
		// When the caller allows mirroring and the ray cannot intersect Z,
		// then swap the Z components of the ray points to force success.
		std::swap(rayStart.Z, rayEnd.Z);

		//Real zOffset = z - rayStart.Z;
		//z = rayStart.Z - zOffset;
	}
#endif

	outWorldPos.x = Vector3::Find_X_At_Z(z, rayStart, rayEnd);
	outWorldPos.y = Vector3::Find_Y_At_Z(z, rayStart, rayEnd);
	outWorldPos.z = z;

	return true;
}

bool W3DViewCornersToWorldAtZ(
	Coord3D &outTopLeft,
	Coord3D &outTopRight,
	Coord3D &outBottomRight,
	Coord3D &outBottomLeft,
	const CameraClass &camera,
	Real z,
	bool allowMirror)
{
	bool ok = true;
	ok &= W3DViewPointToWorldAtZ(outTopLeft, camera, Vector2(-1.0f, 1.0f), z, allowMirror);
	ok &= W3DViewPointToWorldAtZ(outTopRight, camera, Vector2(1.0f, 1.0f), z, allowMirror);
	ok &= W3DViewPointToWorldAtZ(outBottomRight, camera, Vector2(1.0f, -1.0f), z, allowMirror);
	ok &= W3DViewPointToWorldAtZ(outBottomLeft, camera, Vector2(-1.0f, -1.0f), z, allowMirror);
	return ok;
}
