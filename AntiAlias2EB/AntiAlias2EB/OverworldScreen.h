#pragma once

#include "Scene.h"
#include "TileMapRenderer.h"

namespace Screens
{
	class Overworld : public Scene
	{
	public:
		Overworld(const sf::RenderWindow& window);

		void handleEvents(const sf::Event& event) override;
		void update(float fFrameChunk) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TileMapRenderer m_tileMapRenderer;
	};
}