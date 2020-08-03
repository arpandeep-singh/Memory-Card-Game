#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "Card.h"
using namespace std;

class Game {

private :
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	void initializeVariables();
	void initWindow();
	vector<Card*> cards;
	vector<string> textureFiles;
	sf::Texture* backTexture;
	sf::Sprite* playAgainButton;
	sf::Texture* playAgainTexture;
	vector<sf::Texture*> textures;
	Card* tempCard;
	sf::Vector2i mousePosWindow;

	Card* card1;
	bool card1Flipped = false;
	bool card2Flipped = false;
	bool bothCardsMatched = false;
	bool bothCardFlipped = false;
	Card* card2;

	int numOfMoves;
	int numOfCardsOnScreen;
	bool gameOver = false;
	bool mouseHeld = false;


	sf::Font font;
	sf::Text gameOverText;
	sf::Text numOfMovesText;

	sf::SoundBuffer cardMatchbuffer;
	sf::SoundBuffer cardsNoMatchBuffer;
	sf::SoundBuffer cardFlipBuffer;
	sf::SoundBuffer gameStartBuffer;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound cardsMatchSound;
	sf::Sound cardsNotMatchSound;
	sf::Sound cardFlipSound;
	sf::Sound gameOverSound;
	sf::Sound gameStartSound;



public:
	Game();
	~Game();
	const bool isRunning() const; 
	void initTextures();
	void initCards();
	void initSounds();
	void playGame();
	void renderCards();
	void gameLogic();
	void updateMousePositions();
	void pollEvents();
	void update();
	void render();


};
