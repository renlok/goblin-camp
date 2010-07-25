/* Copyright 2010 Ilkka Halila
This file is part of Goblin Camp.

Goblin Camp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Goblin Camp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with Goblin Camp. If not, see <http://www.gnu.org/licenses/>.*/
#include "stdafx.hpp"

#include <CoreFoundation/CoreFoundation.h>
#import  <Carbon/Carbon.h>

#include <boost/filesystem.hpp>
#include <string>
#include <cstring>

namespace fs = boost::filesystem;

void _ImplFindPersonalDirectory(std::string& dir) {
	char buffer[1024];
	CFStringRef username, path;
	username = CSCopyUserName(true);
	path     = CFStringCreateWithFormat(NULL, NULL, CFSTR("/Users/%@/Library/Application Support/Goblin Camp"), username);
	
	CFStringGetCString(path, buffer, sizeof(buffer), kCFStringEncodingUTF8);
	dir = buffer;
	
	CFRelease(username);
	CFRelease(path);
}

void _ImplFindExecutableDirectory(fs::path& exec, fs::path& execDir, fs::path& dataDir) {
	CFBundleRef bundle;
	CFURLRef    execURL, resURL;
	CFStringRef execStr, resStr;
	char execPath[1024], resPath[1024];
	
	bundle  = CFBundleGetMainBundle();
	execURL = CFBundleCopyExecutableURL(bundle);
	resURL  = CFBundleCopyResourcesDirectoryURL(bundle);
	execStr = CFURLCopyFileSystemPath(execURL, kCFURLPOSIXPathStyle);
	resStr  = CFURLCopyFileSystemPath(resURL, kCFURLPOSIXPathStyle);
	
	CFStringGetCString(execStr, execPath, sizeof(execPath), kCFStringEncodingUTF8);
	CFStringGetCString(resStr, resPath, sizeof(resPath), kCFStringEncodingUTF8);
	exec = execPath;
	
	CFRelease(execStr);
	CFRelease(resStr);
	CFRelease(execURL);
	CFRelease(resURL);
	
	exec    = fs::path(std::string(cmdLine));
	execDir = exec.parent_path();
	dataDir = fs::path(std::string(resPath) + "/");
}