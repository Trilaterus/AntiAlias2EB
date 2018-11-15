#include "TileSetData.h"

TileSetData::TileSetData()
{
}

bool TileSetData::isValid() const
{
	bool isValid = isTileSetAttributesValid()
				&& isImageAttributesValid();

	return isValid;
}

bool TileSetData::isTileSetAttributesValid() const
{
	const TileSetAttributes invalidAttributes;
	if (m_tilesetAttributes.m_tileWidth == invalidAttributes.m_tileWidth ||
		m_tilesetAttributes.m_tileHeight == invalidAttributes.m_tileHeight ||
		m_tilesetAttributes.m_columns == invalidAttributes.m_columns)
	{
		return false;
	}

	return true;
}

bool TileSetData::isImageAttributesValid() const
{
	const ImageAttributes invalidAttributes;
	if (m_imageAttributes.m_textureFilePath == invalidAttributes.m_textureFilePath ||
		m_imageAttributes.m_width == invalidAttributes.m_width ||
		m_imageAttributes.m_height == invalidAttributes.m_height)
	{
		return false;
	}

	return true;
}

TileSetData::TileSetAttributes::TileSetAttributes()
	: m_tileWidth(0)
	, m_tileHeight(0)
	, m_margin(0)
	, m_spacing(0)
	, m_columns(0)
{
}

TileSetData::ImageAttributes::ImageAttributes()
	: m_textureFilePath("")
	, m_width(0)
	, m_height(0)
{
}

TileSetData::AnimatedTileFrameAttributes::AnimatedTileFrameAttributes()
	: m_tileId(0)
	, m_durationInMs(0)
{
}

TileSetData::AnimatedTileAttributes::AnimatedTileAttributes()
	: m_baseTileID(0)
{
}
