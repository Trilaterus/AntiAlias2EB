#pragma once

#include "Scene.h"
#include "TileMapRenderer.h"
#include "Player.h"

namespace Screens
{
	class Overworld : public Scene
	{
	public:
		Overworld(const sf::RenderWindow& window);

		void handleEvents(const sf::Event& event) override;
		void update(float frameChunk) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TileMapRenderer m_tileMapRenderer;
		Player m_player;
	};
}