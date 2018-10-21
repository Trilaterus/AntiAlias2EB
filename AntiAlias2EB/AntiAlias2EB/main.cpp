#include <SFML/Graphics.hpp>

#include "TileMapDataSerialiser.h"
#include "TileMapData.h"
#include <vector>
#include <iostream>

void test()
{
	TileMapDataSerialiser serialiser;
	serialiser.createTileMapDataFromFile("../Game/Assets/TiledMaps/FurstTown/furstTown.tmx");
}

int main()
{
	test();

	sf::RenderWindow window(sf::VideoMode(800, 600), "AA2:EB");

	sf::RenderTexture tileMap;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.display();
	}

	return 0;
}