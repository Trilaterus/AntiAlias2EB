#pragma once

#include "Scene.h"

namespace Screens
{
	class AnotherScreen : public Scene
	{
	public:
		AnotherScreen(const sf::RenderWindow& window);

		void handleEvents(const sf::Event& event) override;
		void update(float fFrameChunk) override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}