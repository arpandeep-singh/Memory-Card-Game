#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
namespace FinalProject{
	
	class Card {

	public:
		sf::Sprite* backSprite = nullptr;
		sf::Sprite* frontSprite = nullptr;
		int row = 0;
		int column = 0;
		bool isFacingUp = false;
		bool isVisible = true;

	public:
		Card(sf::Texture* front, sf::Texture* back);
		~Card();
		void flip();
		sf::Sprite* getSprite();
		void setPositionInGrid(int row, int column);
		bool operator==(const Card& other);

	};
}