#include "TextureAnimator.h"

#include "AnimTexture.h"

TextureAnimator::TextureAnimator(const AnimTexture* texture)
	:
	m_pUITexture(texture),
	m_iCurrentFrame(0),
	m_iFrameSpeed(1),
	m_sCurrentAnimation(texture->getFirstAnimationString()),
	m_fTotalFrameChunks(0.f)
{
	
}

sf::IntRect TextureAnimator::getCurrentTextureRect()
{
	return m_pUITexture->getTextureRect(m_sCurrentAnimation, m_iCurrentFrame);
}

void TextureAnimator::changeAnimation(const std::string & sAnimationName)
{
	m_sCurrentAnimation = sAnimationName;
	m_iCurrentFrame = 0; // Reset frame (for now, could do some clever checking for smooth transitions)
}

void TextureAnimator::setFrameSpeed(int iFrameSpeed)
{
	m_iFrameSpeed = std::max(1, iFrameSpeed);
}

void TextureAnimator::updateFrameByTime(float fFrameChunk)
{
	if (m_iFrameSpeed <= 0)
	{
		return;
	}

	m_fTotalFrameChunks += fFrameChunk;

	if (m_fTotalFrameChunks < 1.f / static_cast<float>(m_iFrameSpeed))
	{
		return;
	}
	
	m_fTotalFrameChunks -= 1.f / static_cast<float>(m_iFrameSpeed);

	++m_iCurrentFrame;

	if (m_iCurrentFrame > m_pUITexture->getCurrentNumOfFrames(m_sCurrentAnimation))
	{
		m_iCurrentFrame = 0;
	}
}
