#include "SceneTransition.h"

SceneTransition::SceneTransition()
{
}

void SceneTransition::setScenes(Scene* prevScene, Scene* nextScene)
{
	m_prevScene.reset(prevScene);
	m_nextScene.reset(nextScene);
}
