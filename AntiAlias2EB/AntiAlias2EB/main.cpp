#include <SFML/Graphics.hpp>

#include "TileMapDataSerialiser.h"
#include "TileMapData.h"
#include <vector>
#include <iostream>
#include "TileSetDataSerialiser.h"
#include "TileSetData.h"
#include "TileMapRenderer.h"
#include "SceneManager.h"
#include "OverworldScreen.h"

void test()
{
	const std::string baseFilePath = "../Game/Assets/TiledMaps/FurstTown/";
	const std::string tmxFileName = "furstTown.tmx";

	TileMapDataSerialiser tilemapSerialiser;
	const TileMapData tilemapData = tilemapSerialiser.createTileMapDataFromFile(baseFilePath + tmxFileName);
	const bool isValid = tilemapData.isValid();

	TileSetDataSerialiser tilesetSerialiser;
	TileSetData tilesetData = tilesetSerialiser.createTileSetDataFromFile(baseFilePath + tilemapData.m_tilesets.at(0).m_tilesetFilePath);
	const bool isTilesetValid = tilesetData.isValid();

	TileMapRenderer tilemapRenderer;
	tilemapRenderer.drawToRenderTexture(baseFilePath, tmxFileName);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "AA2:EB");

	sf::Clock clock;
	const float frameRate = 60.f;
	const float secondsPerFrame = 1.f / frameRate;

	SceneManager::getInstance().clearAndAddScreen(new Screens::Overworld(window));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			SceneManager::getInstance().handleEvents(event);
		}

		// This not working to limit the CPU usage, will try to fix using:
		// https://gafferongames.com/post/fix_your_timestep/
		if (clock.getElapsedTime().asSeconds() > secondsPerFrame)
		{
			const float timeElapsed = clock.restart().asSeconds();
			SceneManager::getInstance().update(timeElapsed);

			window.clear();
			window.draw(SceneManager::getInstance());
			window.display();
		}
	}

	return 0;
}