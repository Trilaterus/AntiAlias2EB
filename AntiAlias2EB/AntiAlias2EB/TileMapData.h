#pragma once

#include <vector>

class TileMapData
{
public:
	TileMapData();

	bool isValid();

	struct MapAttributes
	{
		MapAttributes();

		unsigned int m_mapWidth;
		unsigned int m_mapHeight;
		unsigned int m_tileWidth;
		unsigned int m_tileHeight;
	};
	MapAttributes m_mapAttributes;

	struct TilesetAttributes
	{
		TilesetAttributes();

		unsigned int m_firstGID;
		std::string m_tilesetFilePath;
	};
	std::vector<TilesetAttributes> m_tilesets;

	struct ChunkData
	{
		std::vector<unsigned int> m_chunkData;
	};
	std::vector<ChunkData> m_chunks;

private:

	bool isMapAttributesValid();
	bool isTilesetAttributesValid();

};