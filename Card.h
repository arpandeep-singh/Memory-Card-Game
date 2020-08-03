#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Card {

public :
	sf::Sprite* backSprite=nullptr;
	sf::Sprite* frontSprite=nullptr;
	//sf::Texture* texture;
	int row = 0;
	int column = 0;
	bool isFacingUp = true;
	bool isVisible = true;

public :
	Card(sf::Texture* front, sf::Texture* back);
	void flip();
	sf::Sprite* getSprite();
	void setFrontTexture(sf::Texture t);
	void setPositionInGrid(int row, int column);
	bool operator==(const Card& other);

};