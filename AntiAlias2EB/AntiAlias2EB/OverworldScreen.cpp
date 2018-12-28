#include "OverworldScreen.h"

#include "SceneManager.h"
#include "FadeColour.h"
#include "AnotherScreen.h"
#include "TextureManager.h"

namespace Screens
{
	Overworld::Overworld(const sf::RenderWindow& window)
		: Scene(window)
	{
		m_tileMapRenderer.drawToRenderTexture("../Game/Assets/TiledMaps/FurstTown/", "furstTown.tmx");
	}

	void Overworld::handleEvents(const sf::Event& event)
	{
		if (event.type == event.KeyPressed &&
			event.key.code == sf::Keyboard::P)
		{
			SceneManager::getInstance().clearAndAddScreen(new Screens::AnotherScreen(m_Window), new Transition::FadeColour(3.f, sf::Color::Green));
		}

		m_player.handleEvents(event);
	}

	void Overworld::update(float frameChunk)
	{
		m_player.update(frameChunk);
	}

	void Overworld::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		m_tileMapRenderer.drawBehindPlayerTexture(target, states);

		target.draw(m_player);

		m_tileMapRenderer.drawinfrontPlayerTexture(target, states);
	}
}