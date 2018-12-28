#pragma once

#include <SFML\Graphics\RenderTexture.hpp>

#include "TileMapData.h"

class TileMapRenderer
{
public:
	TileMapRenderer();

	bool drawToRenderTexture(const std::string& baseFilePath, const std::string& tmxFileName);

	void drawBehindPlayerTexture(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawinfrontPlayerTexture(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RenderTexture m_behindPlayerTexture;
	sf::RenderTexture m_infrontPlayerTexture;

	void drawRenderTexture(sf::RenderTarget& target, sf::RenderStates states, const sf::RenderTexture& texture) const;
};