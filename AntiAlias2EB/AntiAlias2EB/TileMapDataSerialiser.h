#pragma once

#include <string>

class TileMapData;

class TileMapDataSerialiser
{
public:
	TileMapDataSerialiser();

	const TileMapData createTileMapDataFromFile(const std::string& tmxFilePath) const;
};