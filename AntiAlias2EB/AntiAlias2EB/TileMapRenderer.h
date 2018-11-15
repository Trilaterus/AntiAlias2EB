#pragma once

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Drawable.hpp>

#include "TileMapData.h"

class TileMapRenderer : public sf::Drawable
{
public:
	TileMapRenderer();

	bool drawToRenderTexture(const std::string& baseFilePath, const std::string& tmxFileName);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::RenderTexture m_mapRenderTexture;
private:
};