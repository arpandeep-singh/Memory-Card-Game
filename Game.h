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

namespace FinalProject {
	class Game {

	private:
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;
		vector<Card*> cards;
		vector<string> textureFiles;
		sf::Texture* backTexture;
		sf::Sprite* playAgainButton;
		sf::Texture* playAgainTexture;
		sf::Sprite* quitButton;
		sf::Texture* quitTexture;
		vector<sf::Texture*> textures;
		Card* tempCard;
		sf::Vector2i mousePosWindow;

		Card* card1;
		bool card1Flipped;
		bool card2Flipped;
		bool bothCardsMatched;
		bool bothCardFlipped;
		Card* card2;

		int numOfMoves;
		int numOfCardsOnScreen;
		bool gameOver;
		bool mouseClicked;

		bool quitStatus = false;


		sf::Font font;
		sf::Text gameOverText;
		sf::Text numOfMovesText;

		sf::SoundBuffer cardMatchbuffer;
		sf::SoundBuffer cardsNoMatchBuffer;
		sf::SoundBuffer cardFlipBuffer;
		sf::SoundBuffer gameStartBuffer;
		sf::SoundBuffer gameOverBuffer;
		sf::SoundBuffer menuClickBuffer;
		sf::Sound menuClickSound;
		sf::Sound cardsMatchSound;
		sf::Sound cardsNotMatchSound;
		sf::Sound cardFlipSound;
		sf::Sound gameOverSound;
		sf::Sound gameStartSound;

		void initializeVariables();
		void initWindow();



	public:
		Game();
		~Game();
		void initTextures();
		void initCards();
		void initSounds();
		void playGame();
		void drawCards();
		void gameLogic();
		bool runGame();


	};
}
