#include "AnotherScreen.h"

#include "SceneManager.h"
#include "FadeColour.h"
#include "OverworldScreen.h"

Screens::AnotherScreen::AnotherScreen(const sf::RenderWindow& window)
	: Scene(window)
{
}

void Screens::AnotherScreen::handleEvents(const sf::Event& event)
{
	if (event.type == event.KeyPressed &&
		event.key.code == sf::Keyboard::Space)
	{
		SceneManager::getInstance().clearAndAddScreen(new Screens::Overworld(m_Window), new Transition::FadeColour(3.f, sf::Color::Green));
	}
}

void Screens::AnotherScreen::update(float fFrameChunk)
{
}

void Screens::AnotherScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.clear(sf::Color::Blue);
}
