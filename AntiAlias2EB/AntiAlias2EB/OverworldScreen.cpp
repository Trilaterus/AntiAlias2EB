#include "OverworldScreen.h"

namespace Screens
{
	Overworld::Overworld(const sf::RenderWindow& window)
		: Scene(window)
	{
		m_tileMapRenderer.drawToRenderTexture("../Game/Assets/TiledMaps/FurstTown/", "furstTown.tmx");
	}

	void Overworld::handleEvents(const sf::Event & event)
	{
	}

	void Overworld::update(float fFrameChunk)
	{
	}

	void Overworld::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_tileMapRenderer);
	}
}