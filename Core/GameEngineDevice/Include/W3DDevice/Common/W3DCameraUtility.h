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

#pragma once

class CameraClass;
class Vector2;
class Vector3;
struct Coord3D;

// Returns world-space ray positions originating at a given W3D screen coordinate (-1 to 1)
// and ending at the far clip plane for the given camera.
extern void W3DPickRayPos(
	Vector3 &outRayStart,
	Vector3 &outRayEnd,
	const CameraClass &camera,
	const Vector2 &viewPoint
);

// Returns a world-space ray position originating at a given W3D screen coordinate (-1 to 1)
// and pointing to the view direction of the given camera frustum. The direction vector is a unit vector.
extern void W3DPickRayDir(
	Vector3 &outRayStart,
	Vector3 &outRayDir,
	const CameraClass &camera,
	const Vector2 &viewPoint
);

extern bool W3DViewPointToWorldAtZ(
	Coord3D& outWorldPos,
	const CameraClass &camera,
	const Vector2 &viewPoint,
	Real z,
	bool allowMirror = true
);

extern bool W3DViewCornersToWorldAtZ(
	Coord3D &outTopLeft,
	Coord3D &outTopRight,
	Coord3D &outBottomRight,
	Coord3D &outBottomLeft,
	const CameraClass &camera,
	Real z,
	bool allowMirror = true
);
