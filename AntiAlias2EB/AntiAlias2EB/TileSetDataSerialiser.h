#pragma once

#include <string>

class TileSetData;

class TileSetDataSerialiser
{
public:
	TileSetDataSerialiser();

	const TileSetData createTileSetDataFromFile(const std::string& tsxFilePath) const;
};