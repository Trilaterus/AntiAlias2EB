#pragma once

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Drawable.hpp>

class TileMapRenderer : public sf::Drawable
{
public:
	TileMapRenderer();

	bool drawToRenderTexture();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::RenderTexture m_mapRenderTexture;
};