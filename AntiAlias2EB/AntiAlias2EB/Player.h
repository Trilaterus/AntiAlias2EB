#pragma once

#include "SFML\Graphics.hpp"
#include "AnimTexture.h"
#include "TextureAnimator.h"

class Player : public sf::Drawable
{
public:
	Player();

	void handleEvents(const sf::Event& event);
	void update(float frameChunk);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// Display
	sf::Sprite m_sprite;
	TextureAnimator m_textureAnimator;

	// Movement
	void handleMovement(const sf::Event& event);
	void updateMovement(float frameChunk);

	enum Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	int m_currentDirection;

	float m_currentXSpeed;
	float m_currentYSpeed;
};