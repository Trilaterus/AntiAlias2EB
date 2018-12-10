#include "TileMapDataSerialiser.h"

#include "TileMapData.h"
#include "tinyxml2.h"
#include "StringManipulator.h"

namespace TmxElementNames
{
	const std::string& rootName					= "map";
	const std::string& mapWidthName				= "width";
	const std::string& mapHeightName			= "height";
	const std::string& tileWidthName			= "tilewidth";
	const std::string& tileHeightName			= "tileheight";

		const std::string& tilesetName			= "tileset";
		const std::string& firstGIDName			= "firstgid";
		const std::string& tilesetPathName		= "source";

		const std::string& layerName			= "layer";
		const std::string& layerNameName		= "name";

			const std::string& layerDataName	= "data";

				const std::string& chunkName	= "chunk";
}

TileMapDataSerialiser::TileMapDataSerialiser()
{
}

const TileMapData TileMapDataSerialiser::createTileMapDataFromFile(const std::string& tmxFilePath) const
{
	TileMapData tileMapData;

	tinyxml2::XMLDocument tmxFile;

	tinyxml2::XMLError loadingResult= tmxFile.LoadFile(tmxFilePath.c_str());
	if (loadingResult != tinyxml2::XML_NO_ERROR ||
		loadingResult != tinyxml2::XML_SUCCESS)
	{
		return TileMapData();
	}

	tinyxml2::XMLElement* rootMapData = tmxFile.FirstChildElement(TmxElementNames::rootName.c_str());
	if (rootMapData == nullptr)
	{
		return TileMapData();
	}

	rootMapData->QueryUnsignedAttribute(TmxElementNames::mapWidthName.c_str(), &tileMapData.m_mapAttributes.m_mapWidth);
	rootMapData->QueryUnsignedAttribute(TmxElementNames::mapHeightName.c_str(), &tileMapData.m_mapAttributes.m_mapHeight);
	rootMapData->QueryUnsignedAttribute(TmxElementNames::tileWidthName.c_str(), &tileMapData.m_mapAttributes.m_tileWidth);
	rootMapData->QueryUnsignedAttribute(TmxElementNames::tileHeightName.c_str(), &tileMapData.m_mapAttributes.m_tileHeight);

	tinyxml2::XMLElement* tilesetData = rootMapData->FirstChildElement(TmxElementNames::tilesetName.c_str());
	bool parsingTilesets = true;
	while (parsingTilesets)
	{
		if (tilesetData == nullptr)
		{
			parsingTilesets = false;
			continue;
		}

		TileMapData::TilesetAttributes tilesetAttributes;

		tilesetData->QueryUnsignedAttribute(TmxElementNames::firstGIDName.c_str(), &tilesetAttributes.m_firstGID);
		tilesetAttributes.m_tilesetFilePath = tilesetData->Attribute(TmxElementNames::tilesetPathName.c_str());

		tileMapData.m_tilesets.push_back(tilesetAttributes);

		tilesetData = tilesetData->NextSiblingElement(TmxElementNames::tilesetName.c_str());
	}

	tinyxml2::XMLElement* layerDataRoot = rootMapData->FirstChildElement(TmxElementNames::layerName.c_str());
	bool parsingLayers = true;
	while (parsingLayers)
	{
		if (layerDataRoot == nullptr)
		{
			parsingLayers = false;
			continue;
		}

		TileMapData::LayerData layerData;
		layerData.m_layerName = layerDataRoot->Attribute(TmxElementNames::layerNameName.c_str());

		tinyxml2::XMLElement* layerDataData = layerDataRoot->FirstChildElement(TmxElementNames::layerDataName.c_str());
		if (layerDataData == nullptr)
		{
			// Should always have a <data> tag
			return TileMapData();
		}

		tinyxml2::XMLElement* chunkData = layerDataData->FirstChildElement(TmxElementNames::chunkName.c_str());
		if (chunkData == nullptr)
		{
			// May not always have chunk data (i.e. 'player' layer)
			layerDataRoot = layerDataRoot->NextSiblingElement(TmxElementNames::layerName.c_str());
			continue;
		}

		std::string rawChunkText = chunkData->GetText();
		std::vector<std::string> chunkTexts = StringManipulator::splitString(rawChunkText, ',');
		for (std::string& tileIndexString : chunkTexts)
		{
			StringManipulator::replaceFirstOccurrence(tileIndexString, "\n", "");
			layerData.m_chunkData.push_back(std::stoul(tileIndexString));
		}

		tileMapData.m_layerData.push_back(layerData);

		layerDataRoot = layerDataRoot->NextSiblingElement(TmxElementNames::layerName.c_str());
	}

	return tileMapData;
}
