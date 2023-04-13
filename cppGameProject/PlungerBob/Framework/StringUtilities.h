#pragma once

#include <algorithm>
#include <string>
#include <vector>


static std::string ExtractFileName(const std::string& rString)
{
	if(rString.empty())
		return rString;

	std::size_t FileNameStart = rString.find_last_of("/\\");

	if(FileNameStart >= rString.length())
		FileNameStart = 0;

	else
		++FileNameStart;

	return rString.substr(FileNameStart);
}

static std::string RemoveFileExtension(const std::string& rString)
{
	if(rString.empty())
		return rString;

	size_t FileExtensionStart = rString.find_last_of('.');

	if(FileExtensionStart >= rString.length())
		return rString;

	return rString.substr(0, FileExtensionStart);
}

constexpr uint32_t StringHash(const char* pString, const uint32_t Seed = 0)
{
	uint32_t Hash = 5381 + Seed;

	for(const char* pChar = pString; *pChar; ++pChar)
	{
		Hash = ((Hash << 5) + Hash) ^ (*pChar);
	}

	return Hash;
}