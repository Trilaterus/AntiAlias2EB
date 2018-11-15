#pragma once

#include <string>
#include <vector>

class TileSetData
{
public:
	TileSetData();

	bool isValid() const;

	struct TileSetAttributes
	{
		TileSetAttributes();

		unsigned int m_tileWidth;
		unsigned int m_tileHeight;
		unsigned int m_margin;
		unsigned int m_spacing;
		unsigned int m_columns;
	};
	TileSetAttributes m_tilesetAttributes;

	struct ImageAttributes
	{
		ImageAttributes();

		std::string m_textureFilePath;
		unsigned int m_width;
		unsigned int m_height;
	};
	ImageAttributes m_imageAttributes;

	struct AnimatedTileFrameAttributes
	{
		AnimatedTileFrameAttributes();

		unsigned int m_tileId;
		unsigned int m_durationInMs;
	};
	struct AnimatedTileAttributes
	{
		AnimatedTileAttributes();

		unsigned int m_baseTileID;
		std::vector<AnimatedTileFrameAttributes> m_frames;
	};
	std::vector<AnimatedTileAttributes> m_animatedTiles;

private:
	bool isTileSetAttributesValid() const;
	bool isImageAttributesValid() const;
};