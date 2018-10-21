#pragma once

#include <vector>
#include <string>

namespace StringManipulator
{
	std::vector<std::string> splitString(const std::string& string, const char delimiter);

	void replaceFirstOccurrence(std::string& source, const std::string& toReplace, const std::string& replaceWith);
}