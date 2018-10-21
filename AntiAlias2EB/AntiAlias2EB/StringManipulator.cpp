#include "StringManipulator.h"

#include <sstream>
#include <iostream>

namespace StringManipulator
{
	std::vector<std::string> splitString(const std::string& string, const char delimiter)
	{
		// https://stackoverflow.com/a/5167799
		std::vector<std::string> strings;
		std::istringstream stringToSplit(string);
		std::string currentString;
		while (std::getline(stringToSplit, currentString, delimiter))
		{
			strings.push_back(currentString);
		}

		return strings;
	}

	void replaceFirstOccurrence(std::string& source, const std::string& toReplace, const std::string& replaceWith)
	{
		// https://stackoverflow.com/a/5878802
		std::size_t pos = source.find(toReplace);
		if (pos == std::string::npos)
		{
			return;
		}

		source.replace(pos, toReplace.length(), replaceWith);
	}

}