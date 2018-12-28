/*
Used in non abstract UI classes to manipulate the
AnimTextureInfo in an AnimTexture. This is so that there
is a separate instance of animation per instance.
This class will have info regarding the current
frame, the current animation, the frame rate etc.
*/

#pragma once

#include <string>
#include <SFML\Graphics.hpp>

class AnimTexture;

class TextureAnimator
{
public:
	TextureAnimator(const AnimTexture* texture);

	sf::IntRect getCurrentTextureRect();
	void changeAnimation(const std::string& sAnimationName);
	void setFrameSpeed(int iFrameSpeed);

	void updateFrameByTime(float fFrameChunk);

private:
	const AnimTexture* m_pUITexture;
	int m_iCurrentFrame;
	std::string m_sCurrentAnimation;
	int m_iFrameSpeed; // in frames per second
	float m_fTotalFrameChunks;
};