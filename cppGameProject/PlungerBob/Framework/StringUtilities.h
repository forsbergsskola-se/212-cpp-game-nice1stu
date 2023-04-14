#pragma once

#include <algorithm>
#include <string>
#include <vector>


static std::string RemoveFileExtension(const std::string& rString)
{
	if(rString.empty())
		return rString;

	size_t FileExtensionStart = rString.find_last_of('.');

	if(FileExtensionStart >= rString.length())
		return rString;

	return rString.substr(0, FileExtensionStart);
}