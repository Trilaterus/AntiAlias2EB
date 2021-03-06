#pragma once

#include <vector>

class TileMapData
{
public:
	TileMapData();

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

	struct LayerData
	{
		bool isPlayerLayer() const;

		std::string m_layerName;

		std::vector<unsigned int> m_chunkData;
	};
	std::vector<LayerData> m_layerData;

	bool isValid() const;

private:

	bool isMapAttributesValid() const;
	bool isTilesetAttributesValid() const;
	bool isLayerDataValid() const;

};