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

	std::string removeFileNameFromPath(const std::string& filePath)
	{
		// https://stackoverflow.com/a/10364927
		std::size_t endPos = filePath.find_last_of("\\/");
		if (endPos != std::string::npos)
		{
			// If the last slash is found then add one to the end pos to include the slash
			// i.e. ../path/file.exe -> ../path -> ../path/
			++endPos;
		}
		return filePath.substr(0, endPos);
	}

}