/*
An abstract class containing the needed functionality
for any type of transition.
*/

#pragma once

#include "Scene.h"
#include <memory>

class SceneTransition : public sf::Drawable
{
public:
	SceneTransition();

	void setScenes(Scene* prevScene, Scene* nextScene);

	virtual bool update(float fFrameChunk) = 0; // returns false when complete (it's like asking "is this transitioning?")
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	std::shared_ptr<Scene> m_prevScene;
	std::shared_ptr<Scene> m_nextScene;

private:

};