#include "TileMapData.h"

namespace
{
	const std::string playerLayerName = "player";
}

TileMapData::TileMapData()
{
}

bool TileMapData::isValid() const
{
	bool isValid = isMapAttributesValid() 
				&& isTilesetAttributesValid()
				&& isLayerDataValid();

	return isValid;
}

bool TileMapData::isMapAttributesValid() const
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

bool TileMapData::isTilesetAttributesValid() const
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

bool TileMapData::isLayerDataValid() const
{
	if (isMapAttributesValid() == false)
	{
		return false;
	}

	// tmx file width and height are 0 based (I think?) so increment each when calculating
	const unsigned int expectedChunkSize = (m_mapAttributes.m_mapWidth + 1) * (m_mapAttributes.m_mapHeight + 1);
	for (const auto& layer : m_layerData)
	{
		if (layer.m_chunkData.size() != expectedChunkSize &&
			layer.m_chunkData.size() != 0) // Blank layers are fine (i.e. player layer)
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

bool TileMapData::LayerData::isPlayerLayer() const
{
	return m_layerName == playerLayerName;
}
