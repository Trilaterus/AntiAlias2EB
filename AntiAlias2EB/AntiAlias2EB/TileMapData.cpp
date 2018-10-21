#include "TileMapData.h"

TileMapData::TileMapData()
{
}

bool TileMapData::isValid()
{
	bool isValid = isMapAttributesValid() 
				&& isTilesetAttributesValid();

	return isValid;
}

bool TileMapData::isMapAttributesValid()
{
	const MapAttributes invalidMap;

	if (m_mapAttributes.m_mapWidth == invalidMap.m_mapWidth
		|| m_mapAttributes.m_mapHeight == invalidMap.m_mapHeight
		|| m_mapAttributes.m_tileWidth == invalidMap.m_tileWidth
		|| m_mapAttributes.m_tileHeight == invalidMap.m_tileHeight)
	{
		return false;
	}

	return true;
}

bool TileMapData::isTilesetAttributesValid()
{
	const TileMapData::TilesetAttributes invalidTileset;
	for (const TilesetAttributes tileset : m_tilesets)
	{
		if (tileset.m_firstGID == invalidTileset.m_firstGID
			|| tileset.m_tilesetFilePath == invalidTileset.m_tilesetFilePath)
		{
			return false;
		}
	}

	return true;
}

TileMapData::MapAttributes::MapAttributes()
	: m_mapWidth(0)
	, m_mapHeight(0)
	, m_tileWidth(0)
	, m_tileHeight(0)
{
}

TileMapData::TilesetAttributes::TilesetAttributes()
	: m_firstGID(0)
	, m_tilesetFilePath("")
{
}
