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

//----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright(C) 2001 - All Rights Reserved
//
//----------------------------------------------------------------------------
//
// Project:   Game Engine
//
// Module:    IO
//
// File name: LocalFileSystem.cpp
//
// Created:   4/23/01
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes
//----------------------------------------------------------------------------

#include "PreRTS.h"
#include "Common/LocalFileSystem.h"

//----------------------------------------------------------------------------
//         Externals
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Defines
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Types
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Data
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//         Public Data
//----------------------------------------------------------------------------

LocalFileSystem *TheLocalFileSystem = nullptr;

//----------------------------------------------------------------------------
//         Private Prototypes
//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//         Private Functions
//----------------------------------------------------------------------------

void LocalFileSystem::trimLastPathSegmentInplace(AsciiString& path)
{
	if (const char* end = maxPtr(path.reverseFind('\\'), path.reverseFind('/')))
	{
		path.truncateTo(end - path.str());
	}
	else
	{
		path.clear();
	}
}

void LocalFileSystem::trimTrailingSlash(AsciiString& path)
{
	path.trimEnd('\\');
	path.trimEnd('/');
}

//----------------------------------------------------------------------------
//         Public Functions
//----------------------------------------------------------------------------

Bool LocalFileSystem::ignoreFile(const AsciiString& filename, Bool ignore)
{
	if (filename.isEmpty())
		return false;

	if (ignore)
	{
		m_ignoreFileHashMap.insert(std::make_pair(filename, IgnoreFileData()));
	}
	else if (!m_ignoreFileHashMap.empty())
	{
		m_ignoreFileHashMap.erase(filename);
	}
	return true;
}

Bool LocalFileSystem::ignoreDirectory(const AsciiString& directory, Bool ignore)
{
	if (directory.isEmpty())
		return false;

	if (ignore)
	{
		m_ignoreDirectoryHashMap[directory] = IgnoreFileData();
	}
	else if (!m_ignoreDirectoryHashMap.empty())
	{
		// Lift ignore on this directory and subdirectories
		{
			IgnoreFileHashMap::const_iterator it = m_ignoreDirectoryHashMap.begin();
			while (it != m_ignoreDirectoryHashMap.end())
			{
				IgnoreFileHashMap::const_iterator curr = it++;
				if (startsWithPath(curr->first.c_str(), directory.str()))
				{
					m_ignoreDirectoryHashMap.erase(curr->first);
				}
			}
		}

		// Also lift ignore on files in the directory
		{
			IgnoreFileHashMap::const_iterator it = m_ignoreFileHashMap.begin();
			while (it != m_ignoreFileHashMap.end())
			{
				IgnoreFileHashMap::const_iterator curr = it++;
				if (startsWithPath(curr->first.c_str(), directory.str()))
				{
					m_ignoreFileHashMap.erase(curr->first);
				}
			}
		}
	}
	return true;
}

Bool LocalFileSystem::isFileIgnored(const Char* filename, IgnoreFileTestFlags flags) const
{
	if (*filename == '\0')
		return false;

	// Early out if nothing is ignored.
	if (!hasIgnoredFile() && !hasIgnoredDirectory())
		return false;

	if (m_ignoreFileHashMap.find(IgnoreFileHashMap::key_type::temporary(filename)) != m_ignoreFileHashMap.end())
		return true;

	if (flags & IgnoreFileTestFlags_SkipParentDirectories)
		return false;

	// Also check parent directories.
	AsciiString recurseDirectory = filename;
	trimLastPathSegmentInplace(recurseDirectory);
	return isDirectoryIgnoredRecursive(recurseDirectory, flags);
}

Bool LocalFileSystem::isFileIgnored(const AsciiString& filename, IgnoreFileTestFlags flags) const
{
	if (filename.isEmpty())
		return false;

	// Early out if nothing is ignored.
	if (!hasIgnoredFile() && !hasIgnoredDirectory())
		return false;

	if (m_ignoreFileHashMap.find(filename) != m_ignoreFileHashMap.end())
		return true;

	if (flags & IgnoreFileTestFlags_SkipParentDirectories)
		return false;

	// Also check parent directories.
	AsciiString recurseDirectory = filename;
	trimLastPathSegmentInplace(recurseDirectory);
	return isDirectoryIgnoredRecursive(recurseDirectory, flags);
}

Bool LocalFileSystem::isDirectoryIgnored(const Char* directory, IgnoreFileTestFlags flags) const
{
	if (*directory == '\0')
		return false;

	// Early out if nothing is ignored.
	if (!hasIgnoredDirectory())
		return false;

	if (m_ignoreDirectoryHashMap.find(IgnoreFileHashMap::key_type::temporary(directory)) != m_ignoreDirectoryHashMap.end())
		return true;

	if (flags & IgnoreFileTestFlags_SkipParentDirectories)
		return false;

	// Also check parent directories.
	AsciiString recurseDirectory = directory;
	trimTrailingSlash(recurseDirectory);
	trimLastPathSegmentInplace(recurseDirectory);
	return isDirectoryIgnoredRecursive(recurseDirectory, flags);
}

Bool LocalFileSystem::isDirectoryIgnored(const AsciiString& directory, IgnoreFileTestFlags flags) const
{
	if (directory.isEmpty())
		return false;

	// Early out if nothing is ignored.
	if (!hasIgnoredDirectory())
		return false;

	if (m_ignoreDirectoryHashMap.find(directory) != m_ignoreDirectoryHashMap.end())
		return true;

	if (flags & IgnoreFileTestFlags_SkipParentDirectories)
		return false;

	// Also check parent directories.
	AsciiString recurseDirectory = directory;
	trimTrailingSlash(recurseDirectory);
	trimLastPathSegmentInplace(recurseDirectory);
	return isDirectoryIgnoredRecursive(recurseDirectory, flags);
}

Bool LocalFileSystem::isDirectoryIgnoredRecursive(AsciiString& directory, IgnoreFileTestFlags flags) const
{
	if (directory.isEmpty())
		return false;

	if (m_ignoreDirectoryHashMap.find(directory) != m_ignoreDirectoryHashMap.end())
		return true;

	if (flags & IgnoreFileTestFlags_SkipParentDirectories)
		return false;

	trimLastPathSegmentInplace(directory);
	return isDirectoryIgnoredRecursive(directory, flags);
}

Bool LocalFileSystem::hasIgnoredFile() const
{
	return !m_ignoreFileHashMap.empty();
}

Bool LocalFileSystem::hasIgnoredDirectory() const
{
	return !m_ignoreDirectoryHashMap.empty();
}
