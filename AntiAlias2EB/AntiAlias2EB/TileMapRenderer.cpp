#include "TileMapRenderer.h"

#include "TileMapDataSerialiser.h"
#include "TileSetData.h"
#include "TileSetDataSerialiser.h"
#include "StringManipulator.h"
#include <SFML\Graphics\VertexArray.hpp>
#include <algorithm>
#include <map>
#include <SFML\Graphics\Sprite.hpp>

TileMapRenderer::TileMapRenderer()
{
}

bool TileMapRenderer::drawToRenderTexture(const std::string& baseFilePath, const std::string& tmxFileName)
{
	// Set up TileMapData
	const TileMapDataSerialiser tilemapSerialiser;
	const TileMapData tilemapData = tilemapSerialiser.createTileMapDataFromFile(baseFilePath + tmxFileName);

	if (!tilemapData.isValid())
	{
		return false;
	}

	std::vector<TileSetData> tilesetsData;
	const TileSetDataSerialiser tilesetSerialiser;
	std::map<unsigned int, sf::Texture> textureMap; // The texture related to the GID
	// For each tileset in the tilemap
	for (int i = 0; i < tilemapData.m_tilesets.size(); ++i)
	{
		// Push back the TileSetData
		const std::string fullTilesetDataPath = baseFilePath + tilemapData.m_tilesets.at(i).m_tilesetFilePath;
		const TileSetData tilesetData = tilesetSerialiser.createTileSetDataFromFile(fullTilesetDataPath);
		if (!tilesetData.isValid())
		{
			return false;
		}
		tilesetsData.push_back(tilesetData);

		// Push back the GID + texture
		const std::string fullTilesetTexturePath = StringManipulator::removeFileNameFromPath(fullTilesetDataPath) + tilesetData.m_imageAttributes.m_textureFilePath;
		sf::Texture texture;

		// Have to do it using []'s because for some reason map functions don't want to let me modify the elements
		textureMap[tilemapData.m_tilesets.at(i).m_firstGID] = texture;
		if (!textureMap[tilemapData.m_tilesets.at(i).m_firstGID].loadFromFile(fullTilesetTexturePath))
		{
			return false;
		}
	}

	const unsigned int& mapWidth = tilemapData.m_mapAttributes.m_mapWidth + 1;	 // Size in tile amount (0 based for some monkeying reason)
	const unsigned int& mapHeight = tilemapData.m_mapAttributes.m_mapHeight + 1; // Size in tile amount (0 based for some monkeying reason)
	const unsigned int& tileWidth = tilemapData.m_mapAttributes.m_tileWidth;
	const unsigned int& tileHeight = tilemapData.m_mapAttributes.m_tileHeight;
	m_behindPlayerTexture.create(mapWidth * tileWidth, mapHeight * tileHeight);
	m_infrontPlayerTexture.create(mapWidth * tileWidth, mapHeight * tileHeight);

	bool playerLayerFound = false;
	for (const TileMapData::LayerData& layer : tilemapData.m_layerData)
	{
		if (layer.isPlayerLayer())
		{
			playerLayerFound = true;
		}

		std::vector<sf::VertexArray> vertices;
		vertices.resize(textureMap.size());
		for (sf::VertexArray& vertice : vertices)
		{
			vertice.setPrimitiveType(sf::Quads);
			vertice.resize(mapWidth * mapHeight * 4); // 4 vertices per tile (i.e. each point in the square)
		}

		for (int i = 0; i < layer.m_chunkData.size(); ++i)
		{
			const unsigned int tileID = layer.m_chunkData.at(i);
			if (tileID == 0)
			{
				continue;
			}
			unsigned int textureIndex = 0; // what is the texture index relative to the tileset vector
			unsigned int trueTileId = tileID;
			for (auto it = textureMap.begin(); it != textureMap.end(); ++it)
			{
				if (tileID >= it->first)
				{
					textureIndex = std::distance(textureMap.begin(), it);
					trueTileId = tileID - it->first;
				}
			}

			// Get a point to the start tile's quad
			sf::Vertex* quad = &vertices.at(textureIndex)[i * 4];

			const unsigned int rowPosition = i % mapWidth;
			const unsigned int columnPosition = i / mapWidth;

			quad[0].position = sf::Vector2f(rowPosition * tileWidth, columnPosition * tileHeight);			 // Top left
			quad[1].position = sf::Vector2f((rowPosition + 1) * tileWidth, columnPosition * tileHeight);		 // Top right
			quad[2].position = sf::Vector2f((rowPosition + 1) * tileWidth, (columnPosition + 1) * tileHeight); // Bottom right
			quad[3].position = sf::Vector2f(rowPosition * tileWidth, (columnPosition + 1) * tileHeight);		 // Bottom left

			// only need to find the top left pixel point in the texture, then can use the tile size to get the other points
			const unsigned int& margin = tilesetsData.at(textureIndex).m_tilesetAttributes.m_margin;
			const unsigned int& spacing = tilesetsData.at(textureIndex).m_tilesetAttributes.m_spacing;
			const unsigned int& columns = tilesetsData.at(textureIndex).m_tilesetAttributes.m_columns;
			const unsigned int yCoordinate = trueTileId / columns; // 0 based row index
			const unsigned int xCoordinate = trueTileId % columns; // 0 based column index

			quad[0].texCoords = sf::Vector2f((xCoordinate * (tileWidth + spacing)) + margin, (yCoordinate * (tileHeight + spacing)) + margin); // Top left
			quad[1].texCoords = sf::Vector2f((xCoordinate * (tileWidth + spacing)) + margin + (tileWidth), (yCoordinate * (tileHeight + spacing)) + margin); // Top right
			quad[2].texCoords = sf::Vector2f((xCoordinate * (tileWidth + spacing)) + margin + (tileWidth), (yCoordinate * (tileHeight + spacing)) + margin + (tileHeight)); // Bottom right
			quad[3].texCoords = sf::Vector2f((xCoordinate * (tileWidth + spacing)) + margin, (yCoordinate * (tileHeight + spacing)) + margin + (tileHeight)); // Bottom left
		}

		for (auto it = textureMap.begin(); it != textureMap.end(); ++it)
		{
			const unsigned int verticesIndex = std::distance(textureMap.begin(), it);
			if (playerLayerFound)
			{
				m_infrontPlayerTexture.draw(vertices.at(verticesIndex), &it->second);
			}
			else
			{
				m_behindPlayerTexture.draw(vertices.at(verticesIndex), &it->second);
			}
		}
	}

	m_infrontPlayerTexture.display();
	m_behindPlayerTexture.display();

	return true;
}

void TileMapRenderer::drawBehindPlayerTexture(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawRenderTexture(target, states, m_behindPlayerTexture);
}

void TileMapRenderer::drawinfrontPlayerTexture(sf::RenderTarget & target, sf::RenderStates states) const
{
	drawRenderTexture(target, states, m_infrontPlayerTexture);
}

void TileMapRenderer::drawRenderTexture(sf::RenderTarget& target, sf::RenderStates states, const sf::RenderTexture& texture) const
{
	sf::Sprite sprite(texture.getTexture());
	target.draw(sprite);
}
