#include "TileSetDataSerialiser.h"

#include "TileSetData.h"
#include "tinyxml2.h"

namespace TsxElementNames
{
	const std::string& rootName						= "tileset";
	const std::string& tileWidthName				= "tilewidth";
	const std::string& tileHeightName				= "tileheight";
	const std::string& marginName					= "margin";
	const std::string& spacingName					= "spacing";
	const std::string& columnsName					= "columns";
	
		const std::string& imageName				= "image";
		const std::string& texturePathName			= "source";
		const std::string& textureWidth				= "width";
		const std::string& textureHeight			= "height";

		const std::string& tileName					= "tile";
		const std::string& IdName					= "id";
		
			const std::string& animationName		= "animation";

				const std::string frameName			= "frame";
				const std::string& tileIdName		= "tileid";
				const std::string& durationName		= "duration";
}

TileSetDataSerialiser::TileSetDataSerialiser()
{
}

const TileSetData TileSetDataSerialiser::createTileSetDataFromFile(const std::string & tsxFilePath) const
{
	TileSetData tileSetData;

	tinyxml2::XMLDocument tsxFile;

	tinyxml2::XMLError loadingResult = tsxFile.LoadFile(tsxFilePath.c_str());
	if (loadingResult != tinyxml2::XML_NO_ERROR ||
		loadingResult != tinyxml2::XML_SUCCESS)
	{
		return TileSetData();
	}

	tinyxml2::XMLElement* rootTileSetData = tsxFile.FirstChildElement(TsxElementNames::rootName.c_str());
	if (rootTileSetData == nullptr)
	{
		return TileSetData();
	}

	rootTileSetData->QueryUnsignedAttribute(TsxElementNames::tileWidthName.c_str(), &tileSetData.m_tilesetAttributes.m_tileWidth);
	rootTileSetData->QueryUnsignedAttribute(TsxElementNames::tileHeightName.c_str(), &tileSetData.m_tilesetAttributes.m_tileHeight);
	rootTileSetData->QueryUnsignedAttribute(TsxElementNames::marginName.c_str(), &tileSetData.m_tilesetAttributes.m_margin);
	rootTileSetData->QueryUnsignedAttribute(TsxElementNames::spacingName.c_str(), &tileSetData.m_tilesetAttributes.m_spacing);
	rootTileSetData->QueryUnsignedAttribute(TsxElementNames::columnsName.c_str(), &tileSetData.m_tilesetAttributes.m_columns);

	tinyxml2::XMLElement* imageData = rootTileSetData->FirstChildElement(TsxElementNames::imageName.c_str());
	if (imageData == nullptr)
	{
		return TileSetData();
	}

	tileSetData.m_imageAttributes.m_textureFilePath = imageData->Attribute(TsxElementNames::texturePathName.c_str());

	imageData->QueryUnsignedAttribute(TsxElementNames::textureWidth.c_str(), &tileSetData.m_imageAttributes.m_width);
	imageData->QueryUnsignedAttribute(TsxElementNames::textureHeight.c_str(), &tileSetData.m_imageAttributes.m_height);

	tinyxml2::XMLElement* animatedTileData = rootTileSetData->FirstChildElement(TsxElementNames::tileName.c_str());
	bool parsingAnimations = true;
	while (parsingAnimations)
	{
		if (animatedTileData == nullptr)
		{
			parsingAnimations = false;
			continue;
		}

		TileSetData::AnimatedTileAttributes tileAttributes;
		animatedTileData->QueryUnsignedAttribute(TsxElementNames::IdName.c_str(), &tileAttributes.m_baseTileID);

		tinyxml2::XMLElement* animationData = animatedTileData->FirstChildElement(TsxElementNames::animationName.c_str());
		if (animationData == nullptr)
		{
			parsingAnimations = false;
			continue;
		}

		tinyxml2::XMLElement* frameData = animationData->FirstChildElement(TsxElementNames::frameName.c_str());
		bool parsingFrames = true;
		while (parsingFrames)
		{
			if (frameData == nullptr)
			{
				parsingFrames = false;
				continue;
			}

			TileSetData::AnimatedTileFrameAttributes frameAttributes;
			frameData->QueryUnsignedAttribute(TsxElementNames::tileIdName.c_str(), &frameAttributes.m_tileId);
			frameData->QueryUnsignedAttribute(TsxElementNames::durationName.c_str(), &frameAttributes.m_durationInMs);

			tileAttributes.m_frames.push_back(frameAttributes);

			frameData = frameData->NextSiblingElement(TsxElementNames::frameName.c_str());
		}
		
		tileSetData.m_animatedTiles.push_back(tileAttributes);

		animatedTileData = animationData->NextSiblingElement(TsxElementNames::tileName.c_str());
	}

	return tileSetData;
}
