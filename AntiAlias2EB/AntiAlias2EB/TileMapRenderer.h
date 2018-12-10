#pragma once

#include <SFML\Graphics\RenderTexture.hpp>

#include "TileMapData.h"

class TileMapRenderer
{
public:
	TileMapRenderer();

	bool drawToRenderTexture(const std::string& baseFilePath, const std::string& tmxFileName);


private:
	sf::RenderTexture m_behindPlayerTexture;
	sf::RenderTexture m_infrontPlayerTexture;

};