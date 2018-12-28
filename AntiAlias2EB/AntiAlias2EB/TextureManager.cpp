#include "TextureManager.h"

TextureManager::TextureManager()
{
	
}

TextureManager& TextureManager::getInstance()
{
	static TextureManager instance;
	return instance;
}

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		// Texture failed to load
	}

	this->m_AllTextures[name] = texture;
}

void TextureManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;
	if (!font.loadFromFile(filename))
	{
		// Font failed to load
	}

	this->m_AllFonts[name] = font;
}

void TextureManager::loadAnimTexture(const std::string& name, const std::string& textureFilePath, const std::string& animFilePath)
{
	m_AllAnimTextures[name] = AnimTexture(textureFilePath);
	m_AllAnimTextures[name].addAnimation(animFilePath);
}

sf::Texture& TextureManager::getTexRef(const std::string& texture)
{
	return this->m_AllTextures.at(texture);
}

sf::Font& TextureManager::getFontRef(const std::string& font)
{
	return this->m_AllFonts.at(font);
}

AnimTexture & TextureManager::getAnimTexRef(const std::string& animTex)
{
	return this->m_AllAnimTextures.at(animTex);
}
