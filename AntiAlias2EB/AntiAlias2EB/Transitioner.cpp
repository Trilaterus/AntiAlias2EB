#include "Transitioner.h"

Transitioner::Transitioner()
	:
	m_isTransitioning(false),
	m_currentTransition(nullptr)
{
}

void Transitioner::startTransition(SceneTransition* transition, Scene* prevScene, Scene* nextScene)
{
	m_currentTransition.reset(transition);
	
	m_currentTransition->setScenes(prevScene, nextScene);
	m_isTransitioning = true;
}

bool Transitioner::isTransitioning() const
{
	return m_isTransitioning;
}

void Transitioner::update(float fFrameChunk)
{
	if (m_isTransitioning)
	{
		m_isTransitioning = m_currentTransition->update(fFrameChunk);
		// Don't release transition memory as it still needs to draw
	}
}

void Transitioner::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*m_currentTransition);
}