#include "AnimTexture.h"

#include "AnimTextureInfo.h"

AnimTexture::AnimTexture()
{
	m_pAnimation = nullptr;
	// Needed so it can be initialised in containers (without it being a pointer)
}

AnimTexture::AnimTexture(const std::string& sFilePath)
{
	m_pAnimation = nullptr;
	this->loadFromFile(sFilePath);
}

void AnimTexture::addAnimation(const std::string& sFilePath)
{
	m_pAnimation = new AnimTextureInfo(sFilePath);
}

sf::IntRect AnimTexture::getTextureRect(const std::string& sAnimationName, int iFrameNumber) const
{
	if (m_pAnimation == nullptr)
	{
		return sf::IntRect(0, 0, this->getSize().x, this->getSize().y);
	}

	return m_pAnimation->getTextureRect(sAnimationName, iFrameNumber);
}

std::string AnimTexture::getFirstAnimationString() const
{
	if (m_pAnimation == nullptr)
	{
		return std::string();
	}

	return m_pAnimation->getFirstAnimationString();
}

int AnimTexture::getCurrentNumOfFrames(const std::string& sAnimationName) const
{
	if (m_pAnimation == nullptr)
	{
		return 0;
	}

	return m_pAnimation->getNumOfFrames(sAnimationName);
}
