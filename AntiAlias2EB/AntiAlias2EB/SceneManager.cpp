#include "SceneManager.h"

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::pushScreen(Scene* pScene)
{
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
}

void SceneManager::pushScreen(Scene* pScene, SceneTransition* transition)
{
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
	m_Transitioner.startTransition(transition, m_AllScenes.at(m_AllScenes.size() - 2).get(), m_AllScenes.back().get());
}

void SceneManager::clearAndAddScreen(Scene* pScene)
{
	m_AllScenes.clear();
	m_AllScenes.push_back(std::shared_ptr<Scene>(pScene));
}

void SceneManager::clearAndAddScreen(Scene* pScene, SceneTransition* transition)
{
	std::shared_ptr<Scene> nextScene(pScene);
	m_Transitioner.startTransition(transition, m_AllScenes.back().get(), nextScene.get());
	m_AllScenes.clear();
	m_AllScenes.push_back(nextScene);
}

void SceneManager::popScreen()
{
	m_AllScenes.pop_back();
}

void SceneManager::popScreen(SceneTransition* transition)
{
	m_Transitioner.startTransition(transition, m_AllScenes.back().get(), m_AllScenes.at(m_AllScenes.size() - 2).get());
	m_AllScenes.pop_back();
}

void SceneManager::handleEvents(const sf::Event& event)
{
	if (!m_Transitioner.isTransitioning())
	{
		// May need some null checking...
		m_AllScenes.back()->handleEvents(event);
	}
}

void SceneManager::update(float fFrameChunk)
{
	if (m_Transitioner.isTransitioning())
	{
		m_Transitioner.update(fFrameChunk);
	}

	// May need some null checking...
	m_AllScenes.back()->update(fFrameChunk);
}

void SceneManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_Transitioner.isTransitioning())
	{
		target.draw(m_Transitioner);
	}
	else
	{
		// May need some null checking...
		for (std::vector<std::shared_ptr<Scene>>::const_iterator it = m_AllScenes.begin(); it != m_AllScenes.end(); ++it)
		{
			target.draw(**it);
		}
	}
}

SceneManager::SceneManager()
{
	// Could do with taking in one screen at the start to reduce chance of nullpointering
}
