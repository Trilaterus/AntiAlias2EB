#pragma once

#include <string>

class TileMapData;

class TileMapDataSerialiser
{
public:
	TileMapDataSerialiser();

	TileMapData createTileMapDataFromFile(const std::string& tmxFilePath);
};