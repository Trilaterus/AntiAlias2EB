#include "AnimTextureInfo.h"

#include "tinyxml2.h"

using namespace tinyxml2;

AnimTextureInfo::AnimTextureInfo(const std::string& sTexName)
{
	this->parseFile(sTexName);
}

sf::IntRect AnimTextureInfo::getTextureRect(const std::string& sAnimationName, int iFrameNumber)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		unsigned int frameNumber = std::max(0, iFrameNumber);

		sf::IntRect rect;
		UIAnimFrameInfo info = m_AllAnimations[sAnimationName][iFrameNumber];

		rect.left = info.x;
		rect.top = info.y;
		rect.width = info.w;
		rect.height = info.h;

		return rect;
	}

	return sf::IntRect(-1, -1, -1, -1);
}

std::string AnimTextureInfo::getFirstAnimationString() const
{
	if (m_AllAnimations.empty())
	{
		return std::string();
	}

	return m_AllAnimations.begin()->first;
}

int AnimTextureInfo::getNumOfFrames(const std::string & sAnimationName)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		return m_AllAnimations.at(sAnimationName).size() - 1;
	}

	return 0;
}

int AnimTextureInfo::x(const std::string& sAnimationName, int iFrameNumber)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		unsigned int frameNumber = std::max(0, iFrameNumber);

		return m_AllAnimations[sAnimationName][iFrameNumber].x;
	}

	return 0;
}

int AnimTextureInfo::y(const std::string& sAnimationName, int iFrameNumber)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		unsigned int frameNumber = std::max(0, iFrameNumber);

		return m_AllAnimations[sAnimationName][iFrameNumber].y;
	}

	return 0;
}

int AnimTextureInfo::w(const std::string& sAnimationName, int iFrameNumber)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		unsigned int frameNumber = std::max(0, iFrameNumber);

		return m_AllAnimations[sAnimationName][iFrameNumber].w;
	}

	return 0;
}

int AnimTextureInfo::h(const std::string& sAnimationName, int iFrameNumber)
{
	if (m_AllAnimations.find(sAnimationName) != m_AllAnimations.end())
	{
		unsigned int frameNumber = std::max(0, iFrameNumber);

		return m_AllAnimations[sAnimationName][iFrameNumber].h;
	}

	return 0;
}

void AnimTextureInfo::parseFile(const std::string & sTexName)
{
	XMLDocument doc;
	if (doc.LoadFile(sTexName.c_str()) != XML_NO_ERROR)
	{
		return;
	}

	XMLElement* img = doc.FirstChildElement("img");
	XMLElement* def = img->FirstChildElement("definitions");
	XMLElement* topDir = def->FirstChildElement("dir");

	XMLElement* dir = topDir->FirstChildElement("dir");

	while (dir != nullptr)
	{
		XMLElement* spr = dir->FirstChildElement("spr");

		while (spr != nullptr)
		{
			UIAnimFrameInfo info;

			info.x = spr->IntAttribute("x");
			info.y = spr->IntAttribute("y");
			info.w = spr->IntAttribute("w");
			info.h = spr->IntAttribute("h");

			m_AllAnimations[dir->Attribute("name")].push_back(info);

			spr = spr->NextSiblingElement("spr");
		}

		dir = dir->NextSiblingElement("dir");
	}
}
