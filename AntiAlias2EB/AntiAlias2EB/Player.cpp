#include "Player.h"

#include "TextureManager.h"

namespace
{
	const float c_speed = 1.f;
}

Player::Player()
	: m_textureAnimator(&TextureManager::getInstance().getAnimTexRef("player"))
{
	m_sprite.setTexture(TextureManager::getInstance().getAnimTexRef("player"));

	m_textureAnimator.setFrameSpeed(8);
	m_textureAnimator.changeAnimation("right");

	m_sprite.setTextureRect(m_textureAnimator.getCurrentTextureRect());
}

void Player::handleEvents(const sf::Event& event)
{
	handleMovement(event);
}

void Player::update(float frameChunk)
{
	m_textureAnimator.updateFrameByTime(frameChunk);
	m_sprite.setTextureRect(m_textureAnimator.getCurrentTextureRect());

	updateMovement(frameChunk);

	m_sprite.move(m_currentXSpeed, m_currentYSpeed);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void Player::handleMovement(const sf::Event & event)
{
	// https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
	if (event.type == event.KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			m_currentDirection |= 1UL << Direction::Up;
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			m_currentDirection |= 1UL << Direction::Down;
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			m_currentDirection |= 1UL << Direction::Left;
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			m_currentDirection |= 1UL << Direction::Right;
		}
	}
	else if (event.type == event.KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			m_currentDirection &= ~(1UL << Direction::Up);
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			m_currentDirection &= ~(1UL << Direction::Down);
		}
		else if (event.key.code == sf::Keyboard::Left)
		{
			m_currentDirection &= ~(1UL << Direction::Left);
		}
		else if (event.key.code == sf::Keyboard::Right)
		{
			m_currentDirection &= ~(1UL << Direction::Right);
		}
	}	
}

void Player::updateMovement(float frameChunk) // should probably use the frameChunk?
{
	m_currentXSpeed = 0.f;
	m_currentYSpeed = 0.f;

	// https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
	if ((m_currentDirection >> Direction::Up) & 1U)
	{
		m_currentYSpeed += -c_speed;
	}
	if ((m_currentDirection >> Direction::Down) & 1U)
	{
		m_currentYSpeed += c_speed;
	}
	if ((m_currentDirection >> Direction::Left) & 1U)
	{
		m_currentXSpeed += -c_speed;
	}
	if ((m_currentDirection >> Direction::Right) & 1U)
	{
		m_currentXSpeed += c_speed;
	}

	// Will need to do this?
	// https://gamedev.stackexchange.com/questions/162045/how-do-you-program-diagonal-movement
}
