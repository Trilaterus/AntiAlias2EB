#include <SFML/Graphics.hpp>

#include "TileMapDataSerialiser.h"
#include "TileMapData.h"
#include <vector>
#include <iostream>
#include "TileSetDataSerialiser.h"
#include "TileSetData.h"
#include "TileMapRenderer.h"

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
	//test();
	//sf::Texture blah;
	//blah.loadFromFile("../Game/Assets/Textures/roguelikeChar_transparent.png");

	const std::string baseFilePath = "../Game/Assets/TiledMaps/FurstTown/";
	const std::string tmxFileName = "furstTown.tmx";
	TileMapRenderer tilemapRenderer;
	tilemapRenderer.drawToRenderTexture(baseFilePath, tmxFileName);


	sf::RenderWindow window(sf::VideoMode(800, 600), "AA2:EB");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear();
		window.draw(tilemapRenderer);
		window.display();
	}

	return 0;
}